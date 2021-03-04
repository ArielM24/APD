#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <fstream>
#include <stack>
#include "NumericBase.h"
#include "Alphabet.h"
#include "NumericString.h"
#include "RegularLenguage.h"
#include "stackState.h"
#include "APD.h"


int main(){
    APD automata=APD("APDS/automataPilaN.ap");
    //automata.print();
	cout<<automata.evaluation("aacba")<<endl;
}
