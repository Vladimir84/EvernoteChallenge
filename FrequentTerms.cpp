#include <list>
#include <iostream>
#include <string>
#include <sstream>
#include <queue>
#include <functional>
#include <unordered_map>
#include <map>
#include <set>
#include <memory>
#include <algorithm>

// Understood the problem wrong, this actually finds elements with top k frequencies,
// overkill

namespace MostFrequent{
  // frequency -> hash table
  // top -> min heap, multiple words with same frequency sorted lexecographically -> map 
	

	int readInput(std::unordered_map<std::string,int>& frequencies){
		// read number of words
		std::size_t Nwords;
		std::string _buf;
		getline(std::cin,_buf);
		std::stringstream ss(_buf);
		ss>>Nwords;

		for (int i=0;i<Nwords;i++){
			getline(std::cin,_buf);
			// operator [] calls default value constructor for new key, int is default-contructed to 0
			frequencies[_buf]+=1;
		}

		getline(std::cin,_buf);
		std::stringstream ss1(_buf);
		int k;
		ss1>>k;
		return k;
	}

	typedef std::shared_ptr<std::set<std::string> > _WordList; 
	// frequency and list of words with same frequency
	// number of occurence is second for consistency with items in hash table
	typedef std::pair<_WordList,int> _Elem; 

	struct _Comparator{
		bool operator()(const _Elem& elem1,const _Elem& elem2){
			return elem1.second>elem2.second;
		}
	};

	typedef std::priority_queue<_Elem,std::vector<_Elem>, _Comparator> _TopK;

	void add_to_top_k(_TopK& top_k, int k, const std::pair<std::string,int>& candidate, std::map<int,_WordList>& in_top_k){
		auto insert_into_top_k=[&](){
			_Elem elem;
			elem.second=candidate.second;
			elem.first=_WordList(new std::set<std::string>());
			elem.first->insert(candidate.first);
			top_k.push(elem);
			in_top_k[elem.second]=elem.first;
		};
		// check if number of occurences is already in top_k
		if (in_top_k.find(candidate.second)!=in_top_k.end()){
			in_top_k[candidate.second]->insert(candidate.first);
		} else if (top_k.size()<k){
			// create _WordList
			insert_into_top_k();
		}  else if (top_k.top().second<candidate.second){
			int freq=top_k.top().second;
			top_k.pop();
			in_top_k.erase(freq);
			insert_into_top_k();
		}
	}

	_TopK getTopK(const std::unordered_map<std::string,int>& frequencies, int k){
		_TopK top_k;
		// map of frequencies already in top_k with references to corresponding word list
		std::map<int,_WordList> in_top_k; 

		std::for_each(frequencies.begin(),frequencies.end(),[&](std::pair<std::string, int> item){
			add_to_top_k(top_k,k,item,in_top_k);
		});

		return top_k;
	}

	void printTopK(_TopK& top_k, int k){
		std::list<_Elem> stack;
		while (!top_k.empty()){
			stack.push_front(top_k.top());
			top_k.pop();
		}
                
                std::size_t top_counter(0);
                
		while (!stack.empty()){
                        //std::cout<<"Occurences:"<<stack.front().second<<"\n";
			for (auto elem : *(stack.front().first)){
				std::cout<<elem<<"\n";
                                if (++top_counter>=k) return;
			}
			//std::cout<<*(stack.front().first->begin())<<"\n";
			stack.pop_front();
		}

	}
}

int main(){
	std::unordered_map<std::string,int> frequencies;

	int k=MostFrequent::readInput(frequencies);
	MostFrequent::_TopK top_k(MostFrequent::getTopK(frequencies,k));
	MostFrequent::printTopK(top_k, k);
	
	return 0;
}
