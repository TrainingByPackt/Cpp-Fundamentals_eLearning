﻿#include <future>

struct DatabaseConnection {};

void updateOrderList(DatabaseConnection&) {}
void scheduleOrderProcessing(DatabaseConnection&) {}
/* We need to get a copy of the shared_ptr so it stays alive until this
function finishes */
void updateWithConnection(std::shared_ptr<DatabaseConnection>
connection) {
    updateOrderList(*connection);
}
/* We need to get a copy of the shared_ptr so it stays alive until this
function finishes. */
void scheduleWithConnection(std::shared_ptr<DatabaseConnection>
connection) {
    scheduleOrderProcessing(*connection);
}
int main()
{
    std::shared_ptr<DatabaseConnection> connection = std::make_shared<DatabaseConnection>();
    std::async(std::launch::async, updateWithConnection, connection);
    std::async(std::launch::async, scheduleWithConnection, connection);
}