//---------------------------------------------------------
// from Qt-Exaples
//---------------------------------------------------------

#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QPlainTextEdit>
#include <QObject>

#include "highlighter.h"

class QPaintEvent;
class QResizeEvent;
class QSize;
class QWidget;

class LineNumberArea;

class CodeEditor : public QPlainTextEdit
{
  Q_OBJECT
public:
  CodeEditor(QWidget *parent = 0);
 ~CodeEditor();

private:
  QWidget* lineNumberArea;
  Highlighter* highlighter;
  void syntaxHighlighting();

public:
  void lineNumberAreaPaintEvent(QPaintEvent *event);
  int  lineNumberAreaWidth();

protected:
  void resizeEvent(QResizeEvent *event);

private slots:
  void updateLineNumberAreaWidth(int newBlockCount);
  void highlightCurrentLine();
  void updateLineNumberArea(const QRect &, int);
};


class LineNumberArea : public QWidget
{
public:
  LineNumberArea(CodeEditor *editor) : QWidget(editor)
  {
      codeEditor = editor;
  }
// ~LineNumberArea();

private:
  CodeEditor* codeEditor;

public:
  QSize sizeHint() const
  {
      return QSize(codeEditor->lineNumberAreaWidth(), 0);
  }

protected:
  void paintEvent(QPaintEvent *event)
  {
      codeEditor->lineNumberAreaPaintEvent(event);
  }

};

#endif

