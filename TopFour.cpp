// Lets implement using priority_queue. Its O(n log4), so technically linear
#include <list>
#include <iostream>
#include <string>
#include <sstream>
#include <queue>
#include <functional>


namespace TopFour{
    typedef std::priority_queue<int,std::vector<int>,std::greater<int> > min_priority_queue;

    void add_to_queue(min_priority_queue& top_four,int candidate){
        if (top_four.size()<4){
            top_four.push(candidate);
        } else {
            if (candidate>top_four.top()){
                top_four.pop();
                top_four.push(candidate);
            }
        }
    }

    min_priority_queue get_input(){
        auto readLineFrom_stdin=[](){
            std::string buf;
            int _intbuf;
            std::getline(std::cin,buf);
            std::stringstream ssbuf(buf);
            ssbuf>>_intbuf;
            return _intbuf;
        };
        
        std::size_t Nlines=readLineFrom_stdin();
        min_priority_queue top_four;
        for (std::size_t i=0; i<Nlines; i++){
            add_to_queue(top_four,readLineFrom_stdin());
        }
        return top_four;
    }
}

int main(){
    TopFour::min_priority_queue top_four;
    top_four=TopFour::get_input();
    
    std::list<int> stack; //stack to print out elements of min priority queue in correct order
    
    while (!top_four.empty()){
        stack.push_front(top_four.top());
        top_four.pop();
    }
    
    while (!stack.empty()){
        std::cout<<stack.front()<<"\n";
        stack.pop_front();
    }
    
    return 0;
}
