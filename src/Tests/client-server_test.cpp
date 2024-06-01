#include <gtest/gtest.h>

#include <QCoreApplication>

#include "Client.h"
#include "Server.h"

class QtTestEnvironment : public ::testing::Environment {
 public:
  void SetUp() override {
    int argc = 0;
    char **argv = nullptr;
    app = new QCoreApplication(argc, argv);
  }

  void TearDown() override { delete app; }

  static QCoreApplication *app;
};

QCoreApplication *QtTestEnvironment::app = nullptr;

TEST(ServerClientTest, CommunicationTest) {
  Server server("127.0.0.1", 4900);
  qDebug() << "Server started...";

  Client client("127.0.0.1", 4900);
  qDebug() << "Client started...";

  // To ensure communication happens, you might need a slight delay
  QThread::sleep(1);

  // Here you can add more specific tests to check if the communication was
  // successful
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  ::testing::AddGlobalTestEnvironment(new QtTestEnvironment);

  int ret = RUN_ALL_TESTS();

  return ret;
}
