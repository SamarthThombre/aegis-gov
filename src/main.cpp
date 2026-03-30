#include "control/DecisionEngine.hpp"

int main() {
    // Set back to a realistic 80% threshold
    aegis::control::DecisionEngine engine(80.0);
    engine.run();
    return 0;
}
