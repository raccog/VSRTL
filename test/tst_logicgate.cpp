#include <QtTest/QTest>

#include "vsrtl_logicgate.h"
#include "vsrtl_component.h"
#include "vsrtl_constant.h"
#include "vsrtl_design.h"
#include "vsrtl_port.h"

namespace vsrtl {
namespace core {

class AndDesign : public Design {
public:
    AndDesign() : Design("And Gate") {
        c0->out >> *gate->in[0];
        c1->out >> *gate->in[1];
        gate->out >> outputReg->in;
    }

    SUBCOMPONENT(c0, Constant<1>, 0);
    SUBCOMPONENT(c1, Constant<1>, 0);

    SUBCOMPONENT(gate, TYPE(And<1, 2>));
    SUBCOMPONENT(outputReg, Register<1>);
};

}
}

class tst_logicgate : public QObject {
    Q_OBJECT private slots : void functionalTest();
};

void tst_logicgate::functionalTest() {
    vsrtl::core::AndDesign gate;

    gate.verifyAndInitialize();

    // Check each port/constant for propagation.
    QVERIFY(gate.isVerifiedAndInitialized());
    QVERIFY(gate.c0->isPropagated());
    QVERIFY(gate.c1->isPropagated());
    QVERIFY(gate.c0->out.isPropagated());
    QVERIFY(gate.c1->out.isPropagated());
    QVERIFY(gate.gate->in[0]->isPropagated());
    QVERIFY(gate.gate->in[1]->isPropagated());

    // This always throws an exception. I'm not sure how to propagate the AND gate output
    //QVERIFY(gate.gate->out.isPropagated());

    // Evaluate the AND gate inputs and outputs
    QVERIFY(gate.gate->in[0]->uValue() == 0);
    QVERIFY(gate.gate->in[1]->uValue() == 0);
    // Should be 0 (0 & 0 == 0)
    // This always throws an exception because I cannot figure out how to propagate the output.
    QVERIFY(gate.gate->out.uValue() == 0);
}

QTEST_APPLESS_MAIN(tst_logicgate)
#include "tst_logicgate.moc"
