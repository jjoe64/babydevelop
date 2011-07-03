/*----------*/
/* main.cpp */
/*----------*/

#include <stdlib.h>
#include <iostream>
using namespace std;

#include <QApplication>
#include "babydevelop.h"

int main(int argc, char **argv)
{
	QApplication* programm        = new QApplication(argc, argv);
	BabyDevelop*  programmFenster = new BabyDevelop();

   if(argc>1)
   {
      QString q = *(argv+1);
      programmFenster->oeffnen(q);   
   }

	programm->exec();

	delete programmFenster;
	delete programm;

	return 0;
}

