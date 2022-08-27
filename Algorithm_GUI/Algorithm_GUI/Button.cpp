#include "Button.h"

Button::Button(void)
{
    this->left = 0;
    this->top = 0;
    this->right = 0;
    this->bottom = 0;
    this->str = L"";
}

Button::Button(int _left, int _top, int _right, int _bottom, LPCTSTR _str)
{
    this->left = _left;
    this->top = _top;
    this->right = _right;
    this->bottom = _bottom;
    this->str = _str;
}

bool Button::isClick(ExMessage* msg)
{
    return msg->x >= left && msg->x <= right && msg->y >= top && msg->y <= bottom;
}

void Button::draw(void)
{
    setlinecolor(WHITE);
    rectangle(left, top, right, bottom);
    RECT rect = { left, top, right, bottom };
    drawtext(str, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}
