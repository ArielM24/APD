using namespace std;
class stackState{
    private:
    int state;
    stack<char> data;
    char pop;

    public:
        stackState();
        stackState(int,stack<char>);
        ~stackState();
        int getState();
        void setState(int);
        stack<char> getData();
        void setData(stack<char>);
        void replaceTop(string);
};
stackState::stackState(){
    state=0;
    data=stack<char>();
    pop=0;
}
stackState::~stackState(){
}
stackState::stackState(int state,stack<char> data){
    this->state=state;
    this->data=data;
}
int stackState::getState(){
    return state;
}
void stackState::setState(int state){
    this->state=state;
}
stack<char> stackState::getData(){
    return data;
}
void stackState::setData(stack<char> data){
    this->data=data;
}
void stackState::replaceTop(string top){
    data.pop();
    for(int i = 0; i < top.size(); i++){
        data.push(top[i]);
    }
}
