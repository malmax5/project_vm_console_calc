#pragma once

#include "core/Exceptions.hpp"

#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>
#include <string>

namespace app_calculator::infrastructure
{

template <typename TConnection> class ConnectionPool
{
  public:
    ConnectionPool(const std::string &connInfo, size_t poolSize);
    ~ConnectionPool();

    ConnectionPool(const ConnectionPool &) = delete;
    ConnectionPool &operator=(const ConnectionPool &) = delete;
    ConnectionPool(ConnectionPool &&) noexcept = default;
    ConnectionPool &operator=(ConnectionPool &&) noexcept = default;

    std::shared_ptr<TConnection> acquire();

  private:
    void release(std::shared_ptr<TConnection> connection);

    std::queue<std::shared_ptr<TConnection>> _connections;
    std::mutex _mutex;
    std::condition_variable _condition;
};

} // namespace app_calculator::infrastructure

namespace app_calculator::infrastructure
{

template <typename TConnection>
ConnectionPool<TConnection>::ConnectionPool(const std::string &connInfo, size_t poolSize)
{
    for (size_t i = 0; i < poolSize; ++i)
    {
        try
        {
            _connections.emplace(std::make_shared<TConnection>(connInfo));
        }
        catch (const std::exception &e)
        {
            throw exceptions::DatabaseException(std::string("Failed to create connection: ") +
                                                e.what());
        }
        catch (...)
        {
            throw exceptions::DatabaseException("Failed to create connection: Unknown error");
        }
    }
}

template <typename TConnection> ConnectionPool<TConnection>::~ConnectionPool()
{
    std::lock_guard<std::mutex> lock(_mutex);
    while (!_connections.empty())
    {
        _connections.pop();
    }
}

template <typename TConnection> std::shared_ptr<TConnection> ConnectionPool<TConnection>::acquire()
{
    std::unique_lock<std::mutex> lock(_mutex);
    _condition.wait(lock, [this]() { return !_connections.empty(); });

    auto connection = _connections.front();
    _connections.pop();

    return std::shared_ptr<TConnection>(connection.get(),
                                        [this, connection](TConnection *) { release(connection); });
}

template <typename TConnection>
void ConnectionPool<TConnection>::release(std::shared_ptr<TConnection> connection)
{
    std::lock_guard<std::mutex> lock(_mutex);
    _connections.push(connection);
    _condition.notify_one();
}

} // namespace app_calculator::infrastructure
