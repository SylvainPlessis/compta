BUILT_SOURCES   = .license.stamp

EXTRA_DIST = input_files

check_PROGRAMS  =
check_PROGRAMS += date_unit
check_PROGRAMS += operation_unit
check_PROGRAMS += forecast_container_unit
check_PROGRAMS += forecast_unit
check_PROGRAMS += posting_unit
check_PROGRAMS += history_unit
check_PROGRAMS += account_base_unit
check_PROGRAMS += cash_unit
check_PROGRAMS += savings_unit
check_PROGRAMS += bank_unit
check_PROGRAMS += category_report_unit


AM_CPPFLAGS  = 
AM_CPPFLAGS += -I$(top_srcdir)/src/date/include
AM_CPPFLAGS += -I$(top_srcdir)/src/accounts/include
AM_CPPFLAGS += -I$(top_srcdir)/src/forecast/include
AM_CPPFLAGS += -I$(top_srcdir)/src/money/include
AM_CPPFLAGS += -I$(top_srcdir)/src/parsing/include
AM_CPPFLAGS += -I$(top_srcdir)/src/utilities/include
AM_CPPFLAGS += -I$(top_srcdir)/src/report/include
AM_CPPFLAGS += -I$(top_srcdir)/src/tex/include
AM_CPPFLAGS += -I$(top_srcdir)/src/options/include
AM_CPPFLAGS += -I$(top_builddir)/src/utilities/include #compta_version.h

# Sources for these tests
date_unit_SOURCES = date_unit.cpp
operation_unit_SOURCES = operation_unit.cpp
forecast_container_unit_SOURCES = forecast_container_unit.cpp
forecast_unit_SOURCES = forecast_unit.cpp
posting_unit_SOURCES = posting_unit.cpp
history_unit_SOURCES = history_unit.cpp
account_base_unit_SOURCES = account_base_unit.cpp
cash_unit_SOURCES = cash_unit.cpp
savings_unit_SOURCES = savings_unit.cpp
bank_unit_SOURCES = bank_unit.cpp
category_report_unit_SOURCES = category_report_unit.cpp

#Define tests to actually be run
TESTS  =
XFAIL_TESTS  =
TESTS += date_unit
TESTS += operation_unit
TESTS += forecast_container_unit
TESTS += forecast_unit
TESTS += posting_unit
TESTS += history_unit
TESTS += account_base_unit
TESTS += cash_unit
TESTS += savings_unit
TESTS += bank_unit
TESTS += category_report_unit
TESTS += compta_options.sh
TESTS += compta_fail.sh
XFAIL_TESTS += compta_fail.sh

CLEANFILES =
if CODE_COVERAGE_ENABLED
  CLEANFILES += *.gcda *.gcno
endif

.license.stamp: $(top_srcdir)/LICENSE
	$(top_srcdir)/src/common/lic_utils/update_license.pl $(top_srcdir)/LICENSE \
	$(top_srcdir)/test/*.cpp
	echo 'updated source license headers' >$@

CLEANFILES += .license.stamp

