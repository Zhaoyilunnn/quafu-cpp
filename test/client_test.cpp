#include "quafu/client.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <cpr/cpr.h>

class MockCprWrapper : public quafu::ICprWrapper {
public:
  MOCK_METHOD(cpr::Response, Post,
              (const cpr::Url &url, const cpr::Header &header), (override));
};

TEST(ClientTest, load_account) {
  auto &client = quafu::Client::get_instance();
  auto mock_post = std::make_shared<MockCprWrapper>();
  client.set_cpr_wrapper(mock_post);

  // Set expected return values
  cpr::Response fake_response;
  fake_response.status_code = 200;
  fake_response.text =
      "{\"data\": [{\"system_name\": \"ScQ-P10\", \"system_id\": 0}]}";

  EXPECT_CALL(*mock_post.get(), Post(testing::_, testing::_))
      .WillOnce(testing::Return(fake_response));
  client.load_account();
}
