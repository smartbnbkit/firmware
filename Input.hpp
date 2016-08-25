#ifndef INPUT_HPP
#define INPUT_HPP

class Input {
    static const int MaxInputs = 16;
public:
    void onChanged(uint8_t pin, std::function<void(bool)> callback) {
        m_bits[pin] = (m_bits[pin] << 1) | (!digitalRead(pin));

        if (m_bits[pin] == 0xFFFFFFFF) m_state[pin] |= 1;
        else if (m_bits[pin] == 0)     m_state[pin] &= ~1;

        if ((m_state[pin] & 1) != ((m_state[pin] & 2) >> 1)) {
            callback(m_state[pin] & 1);
        }

        if (m_state[pin] & 1) m_state[pin] |= 2;
        else                  m_state[pin] &= ~2;
    }

    void init(uint8_t pin, uint8_t mode = INPUT_PULLUP) {
        pinMode(pin, mode);
        
        m_bits[pin] = !digitalRead(pin)? 0xFFFFFFFF : 0;

             if (m_bits[pin] == 0xFFFFFFFF) m_state[pin] |= 3;
        else if (m_bits[pin] == 0)          m_state[pin] &= ~3;
    }
private:
    uint32_t m_bits[MaxInputs];
    uint8_t m_state[MaxInputs];
};

#endif
