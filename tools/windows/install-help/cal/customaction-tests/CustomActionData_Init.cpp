// ReSharper disable StringLiteralTypo
#include "stdafx.h"
#include "CustomActionDataTest.h"

TEST_F(CustomActionDataTest, With_DomainUser_Parse_Correctly)
{
    CustomActionData customActionCtx;
    customActionCtx.init(LR"(
    DDAGENTUSER_NAME=TEST\username
)");
    EXPECT_EQ(customActionCtx.Username(), L"TEST\\username");
    EXPECT_EQ(customActionCtx.UnqualifiedUsername(), L"username");
    EXPECT_EQ(customActionCtx.Domain(), L"TEST");
    EXPECT_TRUE(customActionCtx.isUserDomainUser());
    EXPECT_FALSE(customActionCtx.isUserLocalUser());
}

void expect_string_equal(CustomActionData const &customActionData, std::wstring const &prop, std::wstring const &expected)
{
    std::wstring val;
    customActionData.value(prop, val);
    EXPECT_STREQ(val.c_str(), expected.c_str());
}

TEST_F(CustomActionDataTest, With_SingleEmptyProperty_Parse_Correctly)
{
    CustomActionData customActionCtx;
    customActionCtx.init(LR"(
        TEST_PROPERTY=
)");
    expect_string_equal(customActionCtx, L"TEST_PROPERTY", L"");
}

TEST_F(CustomActionDataTest, With_SinglePropertyWithSpacea_Parse_Correctly)
{
    CustomActionData customActionCtx;
    customActionCtx.init(LR"(
        PROP_WITH_SPACE=    
)");
    expect_string_equal(customActionCtx, L"PROP_WITH_SPACE", L"");
}

TEST_F(CustomActionDataTest, With_ManyEmptyProperties_Parse_Correctly)
{
    CustomActionData customActionCtx;
    customActionCtx.init(LR"(
        PROXY_HOST=
        PROXY_PORT=
        PROXY_USER=
)");
    expect_string_equal(customActionCtx, L"PROXY_HOST", L"");
    expect_string_equal(customActionCtx, L"PROXY_PORT", L"");
    expect_string_equal(customActionCtx, L"PROXY_USER", L"");
}

TEST_F(CustomActionDataTest, With_Properties_Parse_Correctly)
{
    CustomActionData customActionCtx;
    customActionCtx.init(LR"(
    TAGS=k1:v1,k2:v2
    HOSTNAME=dd-agent-installopts
    CMD_PORT=4999
    PROXY_HOST=proxy.foo.com
    PROXY_PORT=1234
    PROXY_USER=puser
    PROXY_PASSWORD=ppass
    SITE=eu
    DD_URL=https://someurl.datadoghq.com
    LOGS_DD_URL=https://logs.someurl.datadoghq.com
    PROCESS_DD_URL=https://process.someurl.datadoghq.com
    TRACE_DD_URL=https://trace.someurl.datadoghq.com
)");
    expect_string_equal(customActionCtx, L"TAGS", L"k1:v1,k2:v2");
    expect_string_equal(customActionCtx, L"HOSTNAME", L"dd-agent-installopts");
    expect_string_equal(customActionCtx, L"CMD_PORT", L"4999");
    expect_string_equal(customActionCtx, L"PROXY_HOST", L"proxy.foo.com");
    expect_string_equal(customActionCtx, L"PROXY_PORT", L"1234");
    expect_string_equal(customActionCtx, L"PROXY_USER", L"puser");
    expect_string_equal(customActionCtx, L"PROXY_PASSWORD", L"ppass");
    expect_string_equal(customActionCtx, L"SITE", L"eu");
    expect_string_equal(customActionCtx, L"DD_URL", L"https://someurl.datadoghq.com");
    expect_string_equal(customActionCtx, L"LOGS_DD_URL", L"https://logs.someurl.datadoghq.com");
    expect_string_equal(customActionCtx, L"PROCESS_DD_URL", L"https://process.someurl.datadoghq.com");
    expect_string_equal(customActionCtx, L"TRACE_DD_URL", L"https://trace.someurl.datadoghq.com");
}
