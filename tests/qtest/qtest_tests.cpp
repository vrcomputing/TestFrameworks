#include <Comparator/Comparator.hpp>
#include <QTest>

class CompareTest : public QObject {
  Q_OBJECT

private slots:
  void compareLessThan() { QCOMPARE(compare(2, 3), -1); }

  void compareGreaterThan() { QCOMPARE(compare(3, 2), +1); }

  void compareEqual() { QCOMPARE(compare(3, 3), 0); }
};

QTEST_MAIN(CompareTest)
#include "qtest_tests.moc"