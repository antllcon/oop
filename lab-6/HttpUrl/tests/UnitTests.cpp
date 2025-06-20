#include "HttpUrl.h"
#include "Protocol.h"
#include <gtest/gtest.h>

// нет порта
TEST(HttpUrlTest, ParsesFullHttpUrlWithoutPort)
{
	HttpUrl url("http://example.com/index.html");

	EXPECT_EQ(url.GetProtocol(), Protocol::HTTP);
	EXPECT_EQ(url.GetDomain(), "example.com");
	EXPECT_EQ(url.GetDocument(), "index.html");
	EXPECT_EQ(url.GetPort(), 80);
	EXPECT_EQ(url.GetUrl(), "http://example.com/index.html");
}

// + порт
TEST(HttpUrlTest, ParsesFullHttpsUrlWithNonStandardPort)
{
	HttpUrl url("https://example.com:8443/secure");

	EXPECT_EQ(url.GetProtocol(), Protocol::HTTPS);
	EXPECT_EQ(url.GetDomain(), "example.com");
	EXPECT_EQ(url.GetDocument(), "secure");
	EXPECT_EQ(url.GetPort(), 8443);
	EXPECT_EQ(url.GetUrl(), "https://example.com:8443/secure");
}

TEST(HttpUrlTest, ThrowsOnInvalidProtocol)
{
	EXPECT_THROW(HttpUrl("ftp://example.com/"), UrlParsingError);
}

TEST(HttpUrlTest, ThrowsOnInvalidUrlMissingDomain)
{
	EXPECT_THROW(HttpUrl("http:///index.html"), UrlParsingError);
}

TEST(HttpUrlTest, ThrowsOnInvalidPort)
{
	EXPECT_THROW(HttpUrl("http://example.com:seven/index.html"), UrlParsingError);
}

TEST(HttpUrlTest, ConstructsWithDefaultHttpPortAndAddsSlashToDocument)
{
	HttpUrl url("example.com", "index.html", Protocol::HTTP);

	EXPECT_EQ(url.GetProtocol(), Protocol::HTTP);
	EXPECT_EQ(url.GetDomain(), "example.com");
	EXPECT_EQ(url.GetDocument(), "index.html");
	EXPECT_EQ(url.GetPort(), 80);
	EXPECT_EQ(url.GetUrl(), "http://example.com/index.html");
}

TEST(HttpUrlTest, ConstructsWithExplicitHttpsPort)
{
	HttpUrl url("example.com", "secure", Protocol::HTTPS, 8443);

	EXPECT_EQ(url.GetProtocol(), Protocol::HTTPS);
	EXPECT_EQ(url.GetDomain(), "example.com");
	EXPECT_EQ(url.GetDocument(), "secure");
	EXPECT_EQ(url.GetPort(), 8443);
	EXPECT_EQ(url.GetUrl(), "https://example.com:8443/secure");
}

TEST(HttpUrlTest, GetUrlOmitsStandardPortForHttp)
{
	HttpUrl url("example.com", "test", Protocol::HTTP, 80);
	EXPECT_EQ(url.GetUrl(), "http://example.com/test");
}

TEST(HttpUrlTest, GetUrlOmitsStandardPortForHttps)
{
	HttpUrl url("example.com", "secure", Protocol::HTTPS, 443);
	EXPECT_EQ(url.GetUrl(), "https://example.com/secure");
}

TEST(HttpUrlTest, GetUrlIncludesNonStandardPort)
{
	HttpUrl url("example.com", "custom", Protocol::HTTP, 8080);
	EXPECT_EQ(url.GetUrl(), "http://example.com:8080/custom");
}

TEST(HttpUrlTest, ThrowsOnEmptyDomain)
{
	HttpUrl url("", "doc.html", Protocol::HTTP);
	EXPECT_EQ(url.GetUrl(), "http://localhost/doc.html");
}

TEST(HttpUrlTest, AcceptsRootDocumentExplicitly)
{
	HttpUrl url("example.com", "/", Protocol::HTTP);
	EXPECT_EQ(url.GetDocument(), "/");
	EXPECT_EQ(url.GetUrl(), "http://example.com//");
}

TEST(HttpUrlTest, DomainWithUpperCaseLetters)
{
	HttpUrl url("ExAmPlE.CoM", "page", Protocol::HTTP);
	EXPECT_EQ(url.GetDomain(), "ExAmPlE.CoM");
	EXPECT_EQ(url.GetUrl(), "http://ExAmPlE.CoM/page");
}

// протокол в строке
