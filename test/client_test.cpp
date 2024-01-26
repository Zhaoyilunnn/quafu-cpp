#include "quafu/client.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <cpr/cpr.h>

class MockCprWrapper : public quafu::ICprWrapper {
public:
  MOCK_METHOD(cpr::Response, Post,
              (const cpr::Url &url, const cpr::Header &header), (override));

  MOCK_METHOD(cpr::Response, Post,
              (const cpr::Url &url, const cpr::Header &header,
               const cpr::Payload &payload),
              (override));
};

class TestClient : public quafu::Client {
protected:
  void _load_credential() override { return; }
};

TEST(ClientTest, load_account) {
  auto client = TestClient();
  auto mock_post = std::make_shared<MockCprWrapper>();
  client.set_cpr_wrapper(mock_post);

  // Set expected return values
  cpr::Response fake_response;

  // Backend return successfully
  fake_response.status_code = 200;
  fake_response.text =
      "{\"data\": [{\"system_name\": \"ScQ-P10\", \"system_id\": 0}]}";

  EXPECT_CALL(*mock_post.get(), Post(testing::_, testing::_))
      .WillOnce(testing::Return(fake_response));
  client.load_account();

  // Website error
  fake_response.status_code = 503;
  EXPECT_CALL(*mock_post.get(), Post(testing::_, testing::_))
      .WillOnce(testing::Return(fake_response));

  ASSERT_THROW(client.load_account(), quafu::BackendException);
}
