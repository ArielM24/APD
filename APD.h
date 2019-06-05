using namespace std;
class APD{
    private:
    Alphabet alphabet;
    Alphabet alphabetStack;
    int states;
    vector<stackState> actualStates;
    vector<vector<vector<int>>> transitionFuction;
    vector<int> finalStates;
	bool Lambda;
	int initialState;
	Alphabet getAlphabet(int,string);
	vector<int> getNumbers(string,int);
	char getPop(string);
	stack<char> initialStack;
	RegularLenguage transitionColumns;

    public:
	APD(string fileInput);
	void print();
	void setAlphabet(Alphabet);
	void setAlphabetStack(Alphabet);
	void setInitialState(int);
	void setStates(int);
	void setFinalStates(vector<int>);
	void setInitialStack(stack<char>);
	void setTransitionFuction(vector<vector<vector<int>>>);
	Alphabet getAlphabet();
	Alphabet getAlphabetStack();
	int getStates();
	vector<int> getFinalStates();
	bool getLambda();
	bool getLambda(string);
	int getInitialState();
	stack<char> getInitialStack();
	vector<vector<vector<int>>> getTransitionFuction();
	stack<char> getStack(string);
	void printStack(stack<char>);

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
	}
	else{
		cerr<<"Error tm file"<<endl;
	}	
	
}

void APD:: printStack(stack<char> s){
	while(!s.empty()){
		cout<<s.top()<<endl;
		s.pop();
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
void APD::setTransitionFuction(vector<vector<vector<int>>> f){
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

vector<vector<vector<int>>> APD:: getTransitionFuction(){
	return transitionFuction;
}
