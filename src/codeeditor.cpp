//---------------------------------------------------------
// from Qt-Exaples
//---------------------------------------------------------

#include <QtGui>

#include "codeeditor.h"

CodeEditor::CodeEditor(QWidget *parent) : QPlainTextEdit(parent)
{
  lineNumberArea = new LineNumberArea(this);

  connect(this, SIGNAL(blockCountChanged(int)),            this, SLOT(updateLineNumberAreaWidth(int)));
  connect(this, SIGNAL(updateRequest(const QRect &, int)), this, SLOT(updateLineNumberArea(const QRect &, int)));
  connect(this, SIGNAL(cursorPositionChanged()),           this, SLOT(highlightCurrentLine()));

  updateLineNumberAreaWidth(0);
  highlightCurrentLine();
  
  syntaxHighlighting();
}

CodeEditor::~CodeEditor()
{
}

void CodeEditor::syntaxHighlighting() {
   QFont font;
   font.setFamily("Courier");
   font.setFixedPitch(true);
   font.setPointSize(10);

   setFont(font);

   highlighter = new Highlighter(document());
}

int CodeEditor::lineNumberAreaWidth()
{
  int digits = 1;
  int max = qMax(1, blockCount());
  while (max >= 10)
  {
      max /= 10;
      ++digits;
  }

  int space = 3 + fontMetrics().width(QLatin1Char('9')) * digits;

  return space;
}


void CodeEditor::updateLineNumberAreaWidth(int /* newBlockCount */)
{
  setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}


void CodeEditor::updateLineNumberArea(const QRect &rect, int dy)
{
  if (dy)
      lineNumberArea->scroll(0, dy);
  else
      lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

  if (rect.contains(viewport()->rect()))
      updateLineNumberAreaWidth(0);
}


void CodeEditor::resizeEvent(QResizeEvent *e)
{
  QPlainTextEdit::resizeEvent(e);

  QRect cr = contentsRect();
  lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}


void CodeEditor::highlightCurrentLine()
{
  QList<QTextEdit::ExtraSelection> extraSelections;

  if (!isReadOnly()) {
      QTextEdit::ExtraSelection selection;

      QColor lineColor = QColor(Qt::yellow).lighter(160);

      selection.format.setBackground(lineColor);
      selection.format.setProperty(QTextFormat::FullWidthSelection, true);
      selection.cursor = textCursor();
      selection.cursor.clearSelection();
      extraSelections.append(selection);
  }

  setExtraSelections(extraSelections);
}


void CodeEditor::lineNumberAreaPaintEvent(QPaintEvent *event)
{
  QPainter painter(lineNumberArea);
  painter.fillRect(event->rect(), Qt::lightGray);


  QTextBlock block = firstVisibleBlock();
  int blockNumber = block.blockNumber();
  int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
  int bottom = top + (int) blockBoundingRect(block).height();

  while (block.isValid() && top <= event->rect().bottom())
  {
      if (block.isVisible() && bottom >= event->rect().top())
      {
          QString number = QString::number(blockNumber + 1);
          painter.setPen(Qt::black);
          painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(), Qt::AlignRight, number);
      }

      block = block.next();
      top = bottom;
      bottom = top + (int) blockBoundingRect(block).height();
      ++blockNumber;
  }
}

void CodeEditor::keyPressEvent ( QKeyEvent * e ) {
   // das shift+return event wollen wir nicht, weil sonst ein <br> statt ein <p> gemacht wird
   // return => 16777220
   if ((e->key() == Qt::Key_Enter || e->key() == 16777220) && ((e->modifiers() & Qt::ShiftModifier) == Qt::ShiftModifier)) {
   	// object wird geclont aber ohne shift
   	// aktuelle modifiers & alle möglichen modifiers, außer SHIFT,ALT,CTRL
   	e = new QKeyEvent(e->type(), e->key(), e->modifiers()&Qt::MetaModifier&Qt::KeypadModifier, e->text(), e->isAutoRepeat(), (ushort) e->count());
   }
   QPlainTextEdit::keyPressEvent(e);
}


