#include "delta.hh"

DeltaF::DeltaF() :
    _value(0.0f),
    _diff(0.0f),
    _initialized(false) {}

DeltaF::DeltaF(float value) :
    _value(value),
    _diff(0.0f),
    _initialized(true) {}

void DeltaF::reset() {
    _diff = 0.0f;
    _initialized = false;
}

void DeltaF::tick(float value) {
    if (!_initialized) {
        _diff = 0.0f;
        _value = value;
        _initialized = true;
    } else {
        _diff = value - _value;
        _value = value;
    }
}

float DeltaF::delta() const {
    return _diff;
}
