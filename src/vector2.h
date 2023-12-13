#pragma once
struct Vector2 {
    float x, y;
public:
    Vector2() {
        x = 0;
        y = 0;
    }
    Vector2(int _x, int _y) {
        x = _x;
        y = _y;
    }
    Vector2(float _x, float _y) {
        x = _x;
        y = _y;
    }
    Vector2 operator+ (Vector2& termen) {
        Vector2 rezultat = Vector2(x + termen.x, y + termen.y);
        return rezultat;
    }
    Vector2 operator- (Vector2& termen) {
        Vector2 rezultat = Vector2(x - termen.x, y - termen.y);
        return rezultat;
    }
    Vector2 operator/ (float& numar){
        Vector2 rezultat = Vector2(x / numar, y / numar);
        return rezultat;
    }
    Vector2 operator* (float& numar) {
        Vector2 rezultat = Vector2(x * numar, y * numar);
        return rezultat;
    }
    Vector2 operator/ (const float& numar) const {
        Vector2 rezultat = Vector2(x / numar, y / numar);
        return rezultat;
    }
    Vector2 operator* (const float& numar) const{
        Vector2 rezultat = Vector2(x * numar, y * numar);
        return rezultat;
    }
    bool operator== (Vector2& termen) const {
        return x == termen.x && y == termen.y;
    }
};