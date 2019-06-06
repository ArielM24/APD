typedef struct data{
	int state;
	string top;
}Transition;

/*vector<stackState> addVectorState(vector<stackState> a,vector<Transition> b){
	vector<stackState> result;
	for(int i=0;i<a.size();i++){
		result.push_back(a[i]);
	}
	for(int i=0;i<b.size();i++){
		result.push_back(b[i]);
	}
	return result;
}*/
using namespace std;
class APD{
    private:
    Alphabet alphabet;
    Alphabet alphabetStack;
    int states;
    vector<stackState> actualStates;
    vector<vector<vector<Transition>>> transitionFuction;
    vector<int> finalStates;
	bool Lambda;
	int initialState;
	Alphabet getAlphabet(int,string);
	vector<int> getNumbers(string,int);
	char getPop(string);
	stack<char> initialStack;
	RegularLenguage transitionColumns;
	string getStringFunction(string);
	vector<vector<vector<Transition>>> parseFunction(string,int,int,bool);
    public:
	APD(string fileInput);
	void print();
	void setAlphabet(Alphabet);
	void setAlphabetStack(Alphabet);
	void setInitialState(int);
	void setStates(int);
	void setFinalStates(vector<int>);
	void setInitialStack(stack<char>);
	void setTransitionFuction(vector<vector<vector<Transition>>>);
	Alphabet getAlphabet();
	Alphabet getAlphabetStack();
	int getStates();
	vector<int> getFinalStates();
	bool getLambda();
	bool getLambda(string);
	int getInitialState();
	stack<char> getInitialStack();
	vector<vector<vector<Transition>>> getTransitionFuction();
	stack<char> getStack(string);
	void printStack(stack<char>);
	void printTransitionFuction();
	void printTransitionFuction(vector<vector<vector<Transition>>>);
	vector<int> getClosure(int);
	vector<int> getInt(vector<Transition>);
	void transition(Transition);
	bool evaluation(string);
};

Alphabet APD::getAlphabet(int nAlp,string file){
	ifstream f;
	f.open(file,ios::in);
	if(!f.fail()){
		string typ = "",sym = "";
		Alphabet alf;
		for(unsigned i = 0; i < nAlp*2; i++){
			getline(f,typ);
		}
		getline(f,typ);
		getline(f,sym);
		if(typ=="string:"){
			alf = Alphabet(sym);
		}else if(typ=="range:"){
			int ini,fin;
			ini = getStringNumber(sym,1);
			fin = getStringNumber(sym,2);
			alf = Alphabet(ini,fin);
		}else if(typ=="ascii:"){
			vector<int> ascii = getStringNumbers(sym);
			sym = "";
			for(unsigned i = 0; i < ascii.size(); i++){
				sym += ascii[i];
			}
			alf = Alphabet(sym);
		}
		return alf;
	}else{
		cerr<<"Error tm file"<<endl;
	}
}
vector<int> APD::getNumbers(string file,int line){
	ifstream f;
	f.open(file,ios::in);
	if(!f.fail()){
		vector<int> numbers;
		string aux = "";
		for(unsigned i = 0;i < line; i++){
			getline(f,aux);
		}
		numbers = getStringNumbers(aux);
		return numbers;
	}else{
		cerr<<"Error tm file"<<endl;
	}

}

bool APD::getLambda(string file){
	ifstream f;
	f.open(file,ios::in);
	if(!f.fail()){
		string aux = "";
		for(unsigned i = 0;i < 12; i++){
			getline(f,aux);
		}					
		return aux=="true";
	}else{
		cerr<<"Error tm file"<<endl;
	}
}

APD::APD(string fileIn){
	ifstream fileInput;
	fileInput.open(fileIn,ios::in);
	if(!fileInput.fail()){
		setAlphabet(getAlphabet(0,fileIn));
		setAlphabetStack(getAlphabet(1,fileIn));
		setStates(getNumbers(fileIn,6)[0]);
		setInitialState(getNumbers(fileIn,8)[0]);
		finalStates=getNumbers(fileIn, 10);
		Lambda=getLambda(fileIn);
		initialStack=getStack(fileIn);
		actualStates=vector<stackState>(1,stackState(initialState,initialStack));
		transitionColumns = RegularLenguage(alphabet,alphabetStack.getChars());
		string tr = getStringFunction(fileIn);
		transitionFuction= parseFunction(tr,states,transitionColumns.size(),Lambda);
	}
	else{
		cerr<<"File afnd error"<<endl;
		exit(1);
	}
}

stack<char> APD:: getStack(string file){
	ifstream f;
	stack<char> pila;
	f.open(file,ios::in);
	if(!f.fail()){
		string aux = "";
		for(unsigned i = 0;i < 14; i++){
			getline(f,aux);
		}					
		for(int j=aux.size()-1; j>=0; j--){
			pila.push(aux[j]);
		}	
		return pila;
	}else{
		cerr<<"Error tm file"<<endl;
	}	
}

string APD::getStringFunction(string file){
	ifstream f;
	stack<char> pila;
	f.open(file,ios::in);
	if(!f.fail()){
		string aux = "",tr="";
		for(unsigned i = 0;i < 15; i++){
			getline(f,aux);
		}
		while(!f.eof()){
			getline(f,aux);
			tr+=aux;
		}
		return tr;
	}else{
		cerr<<"Error tm file"<<endl;
	}	
}
//No funciona y no he revisado porque
vector<vector<vector<Transition>>> APD::parseFunction(string function,int _states,int _chars,bool lambda){
	vector<vector<vector<Transition>>> _transitionFuction;
	vector<vector<Transition>> rows;
	vector<Transition> cell;
	Transition temp;
	vector<string> splitTransition = splitString(function,"{");
	vector<string> splitCell;
	int counter = 0;
	if(lambda){
		_chars+=alphabetStack.getChars().size();
	}
	for(int i = 0; i < _states; i++){
		for(int j = 0; j < _chars; j++){
			string aux = splitTransition[counter],aux1;
			aux = eraseEnd(aux,',');
			aux = eraseEnd(aux,'}');
			

			if(aux.size()>1){
				splitCell = splitString(aux,"(");
				for(int k = 0; k < splitCell.size(); k++){
					
					aux1 = splitCell[k];
					aux1 = eraseEnd(aux1,',');
					aux1 = eraseEnd(aux1,')');
					if(splitString(aux1,",",1).size()>1){
						temp = {getStringNumber(aux1),splitString(aux1,",",1)[1]};
					}
					else
						temp = {getStringNumber(aux1), ""};
					cell.push_back(temp);
				}
				rows.push_back(cell);
				cell.clear();
			}else{
				rows.push_back(vector<Transition>(0));
			}
			counter++;
		}
		_transitionFuction.push_back(rows);
		rows.clear();
	}
	return _transitionFuction;
}
void APD:: printStack(stack<char> s){
	while(!s.empty()){
		cout<<s.top()<<endl;
		s.pop();
	}
}


void APD:: printTransitionFuction(vector<vector<vector<Transition>>> t){
	cout<<"Tabla de transicion"<<endl;
	for(int i=0; i<t.size(); i++){
		for(int j=0; j<t[i].size(); j++){
			cout<<"{";
			for(int k=0; k<t[i][j].size(); k++){
				cout<<"("<<t[i][j][k].state<<","<<t[i][j][k].top<<"),";
			}
			cout<<"}";
		}
		cout<<endl;
	}
}

void APD:: printTransitionFuction(){
	cout<<"Tabla de transicion"<<endl;
	for(int i=0; i<transitionFuction.size(); i++){
		cout<<i;
		for(int j=0; j<transitionFuction[i].size(); j++){
			cout<<"{";
			for(int k=0; k<transitionFuction[i][j].size(); k++){
				cout<<"("<<transitionFuction[i][j][k].state<<","<<transitionFuction[i][j][k].top<<"),";
			}
			cout<<"}";
		}
		cout<<endl;
	}
}

void APD::print(){
	cout<<"Alfabeto: ";
	alphabet.print();
	cout<<"Alfabeto de la pila: ";
	alphabetStack.print();
	cout<<"Numero de estados: "<<getStates()<<endl;
	cout<<"Estado Inicial: "<<getInitialState()<<endl;
	cout<<"Estados Finales"<<endl;
	printVectorInt(finalStates, "F=", ",","\n");
	cout<<"Lambda: "<<getLambda()<<endl;
	cout<<"Pila inicial:"<<endl;
	printStack(initialStack);
	cout<<"Columnas:"<<endl;
	transitionColumns.print();
	printTransitionFuction();
}
vector<int> APD::getClosure(int _state){
	vector<int> Closure = vector<int>(1,_state);
	if(Lambda){
		int _char = alphabet.getChars().size(),size1=1,size2;
		vector<int> _Lambda = getInt(transitionFuction[_state][_char]);
		for(int i=0;i<_Lambda.size();i++){
			if(!containsVectorInt(Closure,_Lambda[i])){
				Closure.push_back(_Lambda[i]);
			}
		}
		size2=Closure.size();
		while(size1!=size2){
			for(int i=size1;i<size2;i++){
				_Lambda=getInt(transitionFuction[Closure[i]][_char]);
				for(int j=0;j<_Lambda.size();j++){
					if(!containsVectorInt(Closure,_Lambda[j])){
						Closure.push_back(_Lambda[j]);
					}
				}
			}
			size1=size2;
			size2=Closure.size();
		}
	}
	return Closure;
}
void APD::transition(Transition dat){
	int p = transitionColumns.indexOf(dat.top);
	if(p!=-1){
		vector<int> CL = vector<int>(0);
		vector<stackState> aux;
		for(int i=0;i<actualStates.size();i++){
			CL=mergeVectorInt(CL,getClosure(actualStates[i].getState()));
			aux.push_back(stackState(actualStates[i].getState(),actualStates[i].getData()));
		}
		actualStates=vector<stackState>(0);
		for(int i=0;i<aux.size();i++){
			for(int j = 0; j < transitionFuction[aux[i].getState()][p].size(); j++){
				stackState st = aux[i];
				st.replaceTop(transitionFuction[aux[i].getState()][p][j].top);
				actualStates.push_back(st);
			}
		}
	}
}
bool APD::evaluation(string cad){
	actualStates = vector<stackState>(1,stackState(initialState,initialStack));
	if(!alphabet.isWord(cad)){
		return false;
	}
	for(int i = 0; i < cad.size(); i++){
		for(int j = 0; j < actualStates.size(); j++){
			string aux1 = "";
			aux1.push_back(cad[i]);
			aux1.push_back(initialStack.top());
			Transition aux2 = {actualStates[i].getState(),aux1};
			transition(aux2);
		}
	}
	for(int i = 0; i < actualStates.size(); i++){
		if(containsVectorInt(finalStates,actualStates[i].getState())||
			actualStates[i].getData().empty()){
			return true;
		}
	}
	return false;
}
vector<int> APD::getInt(vector<Transition> t){
	vector<int> result;
	for(int i = 0; i < t.size(); i++){
		result.push_back(t[i].state);
	}
	return result;
}
void APD::setAlphabet(Alphabet f){
	alphabet=f;
}

void APD::setAlphabetStack(Alphabet f){
	alphabetStack=f;
}

void APD::setStates(int i){
	states=i;
}

void APD::setInitialState(int i){
	initialState=i;
}

void APD::setFinalStates(vector<int> f){
	finalStates=f;
}

void APD::setInitialStack(stack<char> stk){
	initialStack=stk;
}
void APD::setTransitionFuction(vector<vector<vector<Transition>>> f){
	transitionFuction=f;
}

Alphabet APD::getAlphabet(){
	return alphabet;
}

Alphabet APD::getAlphabetStack(){
	return alphabetStack;
}

int APD:: getStates(){
	return states;
}

stack<char> APD::getInitialStack(){
	return initialStack;
}
vector<int> APD:: getFinalStates(){
	return finalStates;
}

bool APD:: getLambda(){
	return Lambda;
}

int APD:: getInitialState(){
	return initialState;
}

vector<vector<vector<Transition>>> APD:: getTransitionFuction(){
	return transitionFuction;
}
