#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <vector>

using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArgReferee;

class Report {};

class IReporter {
 public:
  virtual ~IReporter() = default;

  virtual void SendReports() = 0;
};

class IReportBuilder {
 public:
  virtual ~IReportBuilder() = default;

  virtual std::vector<Report> CreateReports() = 0;
};

class IReportSender {
 public:
  virtual ~IReportSender() = default;

  virtual void Send(const Report&) = 0;
};

class ReportBuilder : public IReportBuilder {
 public:
  ~ReportBuilder() override = default;

  std::vector<Report> CreateReports() override {
    std::vector<Report> result;
    // Impl
    result.emplace_back();
    // Impl
    return result;
  }
};

class EmailReportSender : public IReportSender {
 public:
  ~EmailReportSender() override = default;

  void Send(const Report&) override {
    // Some implementation
  }
};

class BadReporter {
 public:
  ~BadReporter() = default;

  void SendReports() {
    IReportBuilder* reportBuilder = new ReportBuilder();
    std::vector<Report> reports = reportBuilder->CreateReports();
    if (reports.empty())
      throw std::runtime_error("reports list is empty");
    IReportSender* reportSender = new EmailReportSender();
    for (const Report& report : reports) {
      reportSender->Send(report);
    }
    delete reportSender;
    delete reportBuilder;
  }
};

class Reporter : public IReporter {
 public:
  Reporter(IReportBuilder* reportBuilder, IReportSender* reportSender)
      : report_builder_(reportBuilder), report_sender_(reportSender) {}

  ~Reporter() override = default;

  void SendReports() override {
    std::vector<Report> reports = report_builder_->CreateReports();
    if (reports.empty())
      throw std::runtime_error("reports list is empty");
    for (const Report& report : reports) {
      // if 
      report_sender_->Send(report);
    }
  }

 private:
  IReportBuilder* report_builder_ = nullptr;
  IReportSender* report_sender_ = nullptr;
};

/// TEST

class MockReportBuilder : public IReportBuilder {
 public:
  MOCK_METHOD0(CreateReports, std::vector<Report>());
};

class MockReportSender : public IReportSender {
 public:
  MOCK_METHOD1(Send, void(const Report&));
};

TEST(ReporterTest, CreateEmptyReports) {
  MockReportBuilder mock_report_builder;
  MockReportSender mock_report_sender;
  Reporter reporter(&mock_report_builder, &mock_report_sender);

  EXPECT_CALL(mock_report_builder, CreateReports())
      .WillOnce(::testing::DoAll(::testing::Return(std::vector<Report>())));

  EXPECT_CALL(mock_report_sender, Send(::testing::_)).Times(0);

  EXPECT_THROW(reporter.SendReports(), std::runtime_error);
}

TEST(ReporterTest, CreateReports) {
  MockReportBuilder mock_report_builder;
  MockReportSender mock_report_sender;
  Reporter reporter(&mock_report_builder, &mock_report_sender);

  const int kCountReports = 42;

  EXPECT_CALL(mock_report_builder, CreateReports())
      .WillOnce(Return(std::vector<Report>(kCountReports)));

  EXPECT_CALL(mock_report_sender, Send(::testing::_)).Times(kCountReports);

  EXPECT_NO_THROW(reporter.SendReports());
}
