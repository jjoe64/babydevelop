/* This file is part of the KDE libraries

   //--------------------------------------------------//
   // modified from ufg@hosengummi.de                  //
   // powerfull modified for BabyDevelop 6... from ufg //
   // for BabyDevelop                                  //
   // http://babydevelop.sourceforge.net               //
   //--------------------------------------------------//

    Copyright (C) 1998 Joerg Habenicht (j.habenicht@europemail.com)

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
    Boston, MA 02111-1307, USA.
*/

/*************************************************************************
 * $Id: kled.cpp,v 1.26 2003/09/06 19:06:31 binner Exp $
 *************************************************************************/

#define PAINT_BENCH
#undef PAINT_BENCH

#ifdef PAINT_BENCH
#include <qdatetime.h>
#include <stdio.h>
#endif


#include <qpainter.h>
#include <qcolor.h>
//ufg//#include <kapplication.h>
//ufg//#include <kpixmapeffect.h>
#include "bled.h"



class BLed::BLedPrivate
{
  friend class BLed;

  int dark_factor;
  QColor offcolor;
};



BLed::BLed(QWidget *parent) : QWidget( parent), led_state(On), led_look(Raised), led_shape(Circular)
{
  QColor col(Qt::green);
  d = new BLed::BLedPrivate;
  d->dark_factor = 300;
  d->offcolor = col.dark(300);

  setColor(col);
}


BLed::BLed(const QColor& col, QWidget *parent) : QWidget( parent), led_state(On), led_look(Raised), led_shape(Circular)
{
  d = new BLed::BLedPrivate;
  d->dark_factor = 300;
  d->offcolor = col.dark(300);

  setColor(col);
  //setShape(Circular);
}

BLed::BLed(const QColor& col, BLed::State state, BLed::Look look, BLed::Shape shape, QWidget *parent) : QWidget(parent),
    led_state(state),
    led_look(look),
    led_shape(shape)
{
  d = new BLed::BLedPrivate;
  d->dark_factor = 300;
  d->offcolor = col.dark(300);

  //setShape(shape);
  setColor(col);
}


BLed::~BLed()
{
  delete d;
}

void
BLed::paintEvent(QPaintEvent *)
{
#ifdef PAINT_BENCH
  const int rounds = 1000;
  QTime t;
  t.start();
  for (int i=0; i<rounds; i++) {
#endif
  switch(led_shape)
    {
    case Rectangular:
      switch (led_look)
 {
 case Sunken :
   paintRectFrame(false);
   break;
 case Raised :
   paintRectFrame(true);
   break;
 case Flat   :
   paintRect();
   break;
 default  :
//ufg//   qWarning("%s: in class BLed: no BLed::Look set",qApp->argv()[0]);
   qWarning("?ufg_1?: in class BLed: no BLed::Look set");
 }
      break;
    case Circular:
      switch (led_look)
 {
 case Flat   :
   paintFlat();
   break;
 case Raised :
   paintRound();
   break;
 case Sunken :
   paintSunken();
   break;
 default:
//ufg//   qWarning("%s: in class BLed: no BLed::Look set",qApp->argv()[0]);
   qWarning("?ufg_2?: in class BLed: no BLed::Look set");
 }
      break;
    default:
//ufg//      qWarning("%s: in class BLed: no BLed::Shape set",qApp->argv()[0]);
      qWarning("?ufg_3?: in class BLed: no BLed::Shape set");
      break;
    }
#ifdef PAINT_BENCH
  }
  int ready = t.elapsed();
  qWarning("elapsed: %d msec. for %d rounds", ready, rounds);
#endif
}

void
BLed::paintFlat() // paint a ROUND FLAT led lamp
{
 QPainter paint;
 QColor color;
 QBrush brush;
 QPen pen;

 // Initialize coordinates, width, and height of the LED
 //
 int width = this->width();
 // Make sure the LED is round!
 if (width > this->height())
  width = this->height();
 width -= 2; // leave one pixel border
 if (width < 0)
   width = 0;


 // start painting widget
 //
 paint.begin( this );

 // Set the color of the LED according to given parameters
    color = ( led_state ) ? led_color : d->offcolor;

 // Set the brush to SolidPattern, this fills the entire area
 // of the ellipse which is drawn with a thin gray "border" (pen)
 brush.setStyle( Qt::SolidPattern );
 brush.setColor( color );

 pen.setWidth( 1 );
 color = color.dark();
 pen.setColor( color );   // Set the pen accordingly

 paint.setPen( pen );   // Select pen for drawing
 paint.setBrush( brush );  // Assign the brush to the painter

 // Draws a "flat" LED with the given color:
 paint.drawEllipse( 1, 1, width, width );

 paint.end();
 //
 // painting done
}

void
BLed::paintRound() // paint a ROUND RAISED led lamp
{
    QPainter paint;
    QColor color;
    QBrush brush;
    QPen pen;

    // Initialize coordinates, width, and height of the LED
    int width = this->width();

    // Make sure the LED is round!
    if (width > this->height())
      width = this->height();
    width -= 2; // leave one pixel border
    if (width < 0) 
      width = 0;

    // start painting widget
    //
    paint.begin( this );

    // Set the color of the LED according to given parameters
    color = ( led_state ) ? led_color : d->offcolor;

    // Set the brush to SolidPattern, this fills the entire area
    // of the ellipse which is drawn first
    brush.setStyle( Qt::SolidPattern );
    brush.setColor( color );
    paint.setBrush( brush );  // Assign the brush to the painter

    // Draws a "flat" LED with the given color:
    paint.drawEllipse( 1, 1, width, width );

    // Draw the bright light spot of the LED now, using modified "old"
    // painter routine taken from KDEUIs BLed widget:

    // Setting the new width of the pen is essential to avoid "pixelized"
    // shadow like it can be observed with the old LED code
    pen.setWidth( 2 );

    // shrink the light on the LED to a size about 2/3 of the complete LED
    int pos = width/5 + 1;
    int light_width = width;
    light_width *= 2;
    light_width /= 3;

    // Calculate the LEDs "light factor":
    int light_quote = (130*2/(light_width?light_width:1))+100;

    // Now draw the bright spot on the LED:
    while (light_width) {
     color = color.light( light_quote );   // make color lighter
 pen.setColor( color );    // set color as pen color
 paint.setPen( pen );    // select the pen for drawing
 paint.drawEllipse( pos, pos, light_width, light_width ); // draw the ellipse (circle)
 light_width--;
    if (!light_width)
        break;
 paint.drawEllipse( pos, pos, light_width, light_width );
 light_width--;
 if (!light_width)
    break;
 paint.drawEllipse( pos, pos, light_width, light_width );
 pos++; light_width--;
    }

    // Drawing of bright spot finished, now draw a thin gray border
    // around the LED; it looks nicer that way. We do this here to
    // avoid that the border can be erased by the bright spot of the LED

    pen.setWidth( 1 );
    color = color.dark();
    pen.setColor( color );   // Set the pen accordingly
    paint.setPen( pen );   // Select pen for drawing
    brush.setStyle( Qt::NoBrush );  // Switch off the brush
    paint.setBrush( brush );   // This avoids filling of the ellipse

    paint.drawEllipse( 1, 1, width, width );

    paint.end();
    //
    // painting done
}

void
BLed::paintSunken() // paint a ROUND SUNKEN led lamp
{
    QPainter paint;
    QColor color;
    QBrush brush;
    QPen pen;
    
    // First of all we want to know what area should be updated
    // Initialize coordinates, width, and height of the LED
    int width = this->width();

    // Make sure the LED is round!
    if (width > this->height())
      width = this->height();
    width -= 2; // leave one pixel border
    if (width < 0) 
      width = 0;

    // maybe we could stop HERE, if width <=0 ?

    // start painting widget
    //
    paint.begin( this );

    // Set the color of the LED according to given parameters
    color = ( led_state ) ? led_color : d->offcolor;

    // Set the brush to SolidPattern, this fills the entire area
    // of the ellipse which is drawn first
    brush.setStyle( Qt::SolidPattern );
    brush.setColor( color );
    paint.setBrush( brush );                // Assign the brush to the painter

    // Draws a "flat" LED with the given color:
    paint.drawEllipse( 1, 1, width, width );

    // Draw the bright light spot of the LED now, using modified "old"
    // painter routine taken from KDEUIs BLed widget:

    // Setting the new width of the pen is essential to avoid "pixelized"
    // shadow like it can be observed with the old LED code
    pen.setWidth( 2 );

    // shrink the light on the LED to a size about 2/3 of the complete LED
    int pos = width/5 + 1;
    int light_width = width;
    light_width *= 2;
    light_width /= 3;
 
    // Calculate the LEDs "light factor":
    int light_quote = (130*2/(light_width?light_width:1))+100;

    // Now draw the bright spot on the LED:
    while (light_width) {
 color = color.light( light_quote );                      // make color lighter
 pen.setColor( color );                                   // set color as pen color
 paint.setPen( pen );                                     // select the pen for drawing
 paint.drawEllipse( pos, pos, light_width, light_width ); // draw the ellipse (circle)
 light_width--;
 if (!light_width)
  break;
 paint.drawEllipse( pos, pos, light_width, light_width );
 light_width--;
 if (!light_width)
  break;
 paint.drawEllipse( pos, pos, light_width, light_width );
 pos++; light_width--;
    }

    // Drawing of bright spot finished, now draw a thin border
    // around the LED which resembles a shadow with light coming
    // from the upper left.

    pen.setWidth( 3 ); // ### shouldn't this value be smaller for smaller LEDs?
    brush.setStyle( Qt::NoBrush );              // Switch off the brush
    paint.setBrush( brush );                        // This avoids filling of the ellipse

    // Set the initial color value to colorGroup().light() (bright) and start
    // drawing the shadow border at 45 (45*16 = 720).

    int angle = -720;
    color = color.light();
    
    for ( int arc = 120; arc < 2880; arc += 240 ) {
      pen.setColor( color );
      paint.setPen( pen );
      paint.drawArc( 1, 1, width, width, angle + arc, 240 );
      paint.drawArc( 1, 1, width, width, angle - arc, 240 );
      color = color.dark( 110 ); //FIXME: this should somehow use the contrast value
    } // end for ( angle = 720; angle < 6480; angle += 160 )

    paint.end();
    //
    // painting done
}

void
BLed::paintRect()
{
  QPainter painter(this);
  QBrush lightBrush(led_color);
  QBrush darkBrush(d->offcolor);
  QPen pen(led_color.dark(300));
  int w=width();
  int h=height();
  // -----
  switch(led_state)
  {
  case On:
    painter.setBrush(lightBrush);
    painter.drawRect(0, 0, w, h);
    break;
  case Off:
    painter.setBrush(darkBrush);
    painter.drawRect(0, 0, w, h);
    painter.setPen(pen);
    painter.drawLine(0, 0, w, 0);
    painter.drawLine(0, h-1, w, h-1);
    // Draw verticals
    int i;
    for(i=0; i < w; i+= 4 /* dx */)
      painter.drawLine(i, 1, i, h-1);
    break;
  default: break;
  }
}

void
BLed::paintRectFrame(bool raised)
{
  QPainter painter(this);
  QBrush lightBrush(led_color);
  QBrush darkBrush(d->offcolor);
  int w=width();
  int h=height();
  QColor black=Qt::black;
  QColor white=Qt::white;
  // -----
  if(raised)
    {
      painter.setPen(white);
      painter.drawLine(0, 0, 0, h-1);
      painter.drawLine(1, 0, w-1, 0);
      painter.setPen(black);
      painter.drawLine(1, h-1, w-1, h-1);
      painter.drawLine(w-1, 1, w-1, h-1);
      painter.fillRect(1, 1, w-2, h-2,
                (led_state==On)? lightBrush : darkBrush);
    } else {
      painter.setPen(black);
      painter.drawRect(0,0,w,h);
      painter.drawRect(0,0,w-1,h-1);
      painter.setPen(white);
      painter.drawRect(1,1,w-1,h-1);
      painter.fillRect(2, 2, w-4, h-4,
         (led_state==On)? lightBrush : darkBrush);
    }
}

BLed::State
BLed::state() const
{
  return led_state;
}

BLed::Shape
BLed::shape() const
{
  return led_shape;
}

QColor
BLed::color() const
{
  return led_color;
}

BLed::Look
BLed::look() const
{
  return led_look;
}

void
BLed::setState( State state )
{
  if (led_state != state)
    {
      led_state = state;
      update();
    }
}

void
BLed::toggleState()
{
  // Funktionprototyp in Zeile 196 in ufgled.h //
  led_state = (led_state == On) ? Off : On;
  // setColor(led_color);
  update();
}

void
BLed::setShape(BLed::Shape s)
{
  if(led_shape!=s)
    {
      led_shape = s;
      update();
    }
}

void
BLed::setColor(const QColor& col)
{
  if(led_color!=col) {
    led_color = col;
    d->offcolor = col.dark(d->dark_factor);
    update();
  }
}

void
BLed::setDarkFactor(int darkfactor)
{
  if (d->dark_factor != darkfactor) {
    d->dark_factor = darkfactor;
    d->offcolor = led_color.dark(darkfactor);
    update();
  }
}

int
BLed::darkFactor() const
{
  return d->dark_factor;
}

void
BLed::setLook( Look look )
{
  if(led_look!=look)
    {
      led_look = look;
      update();
    }
}

void
BLed::toggle()
{
  toggleState();
}

void
BLed::on()
{
  setState(On);
}

void
BLed::off()
{
  setState(Off);
}

QSize
BLed::sizeHint() const
{
  return QSize(16, 16);
}

QSize
BLed::minimumSizeHint() const
{
  return QSize(16, 16 );
}

void BLed::virtual_hook( int, void* )
{ /*BASE::virtual_hook( id, data );*/ }

