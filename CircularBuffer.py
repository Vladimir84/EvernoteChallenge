#Enter your code here
import sys
class CircularBuffer:
    '''
        Circular buffer implemented using Python's list. 
        Append/Remove one element - O(1) 
    '''
    def __init__(self,N):
        self.N=N
        self.container=[None]*N
        self.first=self.last=0

    def append(self,to_append):
        for el in to_append:
            if not self.first==self.last and self.first%self.N==self.last%self.N:
                # don't let pointers to get too large
                self.first%=self.N
                self.last=self.first+self.N
                self.first+=1
            self.container[self.last%self.N]=el
            self.last+=1
            
    def remove(self,n):
        # since python's list implemented using array, actual removal of elements 
        # would be too expensive, shift pointer instead
        if (self.last-self.first)>=n:
            self.first+=n


    def __str__(self):
        if self.first==self.last: return ''
        s=str(self.container[self.first%self.N]).strip()
        to_print=self.first+1
        while not to_print==self.last:
            s+='\n'+str(self.container[to_print%self.N]).strip()
            to_print+=1
        return s

def Append(all_lines,tokens,cb):
    nLines2append=int(tokens[1])
    for _ in range(nLines2append):
        elem=all_lines.next()
        cb.append([elem])

def Remove(f,tokens,cb): 
    cb.remove(int(tokens[1]))

def ListElems(f,tokens,cb):
    print cb

def Quit(f,tokens,cb):
    raise SystemExit(0)

def controlFlow():
            commands={
                'A':Append,
                'R':Remove,
                'L':ListElems,
                'Q':Quit
            }
            all_lines=iter(sys.stdin.readlines())
            cb=CircularBuffer(int(all_lines.next()))  
                
            for line in all_lines:
                tokens=line.split()
                commands.get(tokens[0],Quit)(all_lines,tokens,cb)
                
if __name__ == "__main__":                
    controlFlow()
