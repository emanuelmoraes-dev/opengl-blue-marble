#ifndef _OPENGL_BLUE_MARBLE_DELTA_HH_INCLUDED_
#define _OPENGL_BLUE_MARBLE_DELTA_HH_INCLUDED_

class DeltaF {
private:
    float _value;
    float _diff;
    bool _initialized;
public:
    DeltaF();
    DeltaF(float value);
    void reset();
    void tick(float value);
    float delta() const;
};

#endif
