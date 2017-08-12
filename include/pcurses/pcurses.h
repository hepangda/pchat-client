/**********************************************************************************
 * Copyright (c) 2017- Pangda                                                     *
 *                                                                                *
 * Permission is hereby granted, free of charge, to any person obtaining a copy   *
 * of this software and associated documentation files (the "Software"), to deal  *
 * in the Software without restriction, including without limitation the rights   *
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell      *
 * copies of the Software, and to permit persons to whom the Software is          *
 * furnished to do so, subject to the following conditions:                       *
 *                                                                                *
 * The above copyright notice and this permission notice shall be included in all *
 * copies or substantial portions of the Software.                                *
 *                                                                                *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR     *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,       *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE    *
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER         *
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  *
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  *
 * SOFTWARE.                                                                      *
 *                                                                                *
 * Except as contained in this notice, the name(s) of the above copyright         *
 * holders shall not be used in advertising or otherwise to promote the           *
 * sale, use or other dealings in this Software without prior written             *
 * authoriztion.                                                                  *
 **********************************************************************************/
 /*********************************************************************************
  *    Author: Hepangda <ryozeho@gmail.com>   2017-on                             *
  *********************************************************************************/
#include<ncurses.h>
#include<locale.h>
#include<unistd.h>

namespace pcurses {

class Global {
private:
    virtual void DoNotInstance() = 0;
public:
    static int SetCbreak();
    static int SetCooked();
    static int SetEcho(bool status);
    static int SetKeypad(bool status);
    static int Flash();

};
/*  A_NORMAL       正常模式
 *  A_STANDOUT     高亮
 *  A_UNDERLINE    下划线
 *  A_REVERSE      反色
 *  A_BLINK        闪烁
 *  A_DIM          暗色
 *  A_BOLD         加粗
 *  A_PROTECT      Protected mode
 *  A_INVIS        Invisible or blank mode
 *  A_ALTCHARSET   Alternate character set
 *  A_ITALIC       斜体
 *  A_CHARTEXT     Bit-mask to extract a character
 */

class ConsoleContain {
public:
    WINDOW *self;
    virtual void DoNotInstance() = 0;
public:
    int Clear();
    int DrawBorder(char left = '|', char right = '|', char top = '-',
                   char bottom = '-', char topleft = '+', char topright = '+',
                   char botleft = '+', char botright = '+');
    int Putchar(char which);
    int PutcharAtPos(int y, int x, char which);
    int Print(char *format, ...);
    int PrintAt(int y, int x, char *format, ...);
    int Scan(char *format, ...);
    int ScanfAt(int y, int x, char *format, ...);
    int MoveTo(int y, int x);
    int Refresh();
    int Getchar();
    int EnableScroll(bool status);
    int SetScroll(int page);
    int SetAttribute(chtype attr);
    int CancelAttribute();
};

class Window : public ConsoleContain {
protected:
    void DoNotInstance() {}
    int line, col, starty, startx;
public:
    Window(int line, int col, int starty, int startx);
    ~Window();
};

class Screen : public ConsoleContain {
protected:
    void DoNotInstance() {}
public:
    int lines;
    int cols;
    Screen();
    ~Screen();
};

class Pad : public ConsoleContain {
protected:
    void DoNotInstance() {}
    int line, col, starty, startx;
    int now;
public:
    Pad(int line, int col, int starty, int startx);
    ~Pad();
    int Refresh();
    int SetScroll(int page);
    int FitScroll();
    int EraseChar();
};

}
