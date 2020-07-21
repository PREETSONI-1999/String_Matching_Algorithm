// C++ implementation of search and insert 
// operations on Trie 
#include <bits/stdc++.h> 

using namespace std; 

const int ALPHABET_SIZE = 26; 
int init_sr=0;
int ctr=0;
int fav;
// trie node 

vector<string> genes;
vector<long long int>sums;
struct TrieNode 
{ 
    struct TrieNode *children[ALPHABET_SIZE]; 
    struct TrieNode *reverse;
    // isEndOfWord is true if the node represents 
    // end of a word 
    
    bool isEndOfWord; 
    
    int sr_no;
    int out;
}; 
queue<TrieNode*>box;
// Returns new trie node (initialized to NULLs) 
struct TrieNode *getNode(void) 
{ 
    struct TrieNode *pNode = new TrieNode; 

    pNode->isEndOfWord = false; 
    pNode->sr_no=init_sr;
    init_sr++;
    
    for (int i = 0; i < ALPHABET_SIZE; i++) 
        pNode->children[i] = NULL; 

    return pNode; 
} 


vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}



// If not present, inserts key into trie 
// If the key is prefix of trie node, just 
// marks leaf node 
void insertt(struct TrieNode *root, string key,int key_index) 
{ 
    struct TrieNode *pCrawl = root; 
    
    for (int i = 0; i < key.length(); i++) 
    { 
        int index = key[i] - 'a'; 
        //cout<<"index : " <<key[i] <<"i.e " <<index <<"\n";
        if (!pCrawl->children[index]) 
            pCrawl->children[index] = getNode(); 

        pCrawl = pCrawl->children[index]; 
    } 

    // mark last node as leaf 
    pCrawl->isEndOfWord = true;
    if(!pCrawl->out)
    pCrawl->out=pCrawl->out | (1<<key_index);
    
    //cout<<"out " <<pCrawl->out <<"\n";
    
    
} 
void recurse(struct TrieNode *pCrawlslow)
{    
        //cout<<"sr_no  " <<pCrawlslow->sr_no <<" \n ";
    for(int i=0;i<26;i++)
    {
    
        if(pCrawlslow->children[i] )
        {  
        //    cout<<(pCrawlslow->reverse)->sr_no <<"\n";
             recurse(pCrawlslow->children[i]);
        }
        
        
    }
    //cout<<"out " <<pCrawlslow->out <<"\n";
    if(pCrawlslow->isEndOfWord)
    {
        //cout<<"ends at sr_no " <<pCrawlslow->sr_no <<"\n";
        map<int,int>::iterator it;
//        for(it=(pCrawlslow->m).begin();it!=(pCrawlslow->m).end();it++)
//        {
//           // cout<<"index : " <<it->first <<" health : " <<it->second <<"\n";
//        }
    }
    
}

void settree(struct TrieNode *pCrawlslow)
{    
        struct TrieNode *point=pCrawlslow;
        point->reverse=point;
        
    for(int i=0;i<26;i++)
    {
        if(point->children[i])
        {    
                box.push(point->children[i]);
                point->children[i]->reverse=point;
              //  cout<<(char)('A'+i) <<" ";
        }

    }
    struct TrieNode *tempo;
    while(!box.empty())
    {
        int j;
           
                for(int i=0;i<26;i++)
                {    
                    if(box.front()->children[i])
                    {    
//                        cout<<"\nbox ka " <<(char)('A'+i) <<" child hai\n";
//                        for(j=0;j<26;j++)
//                        {
//                            if((box.front()->reverse)->children[j])
//                            {
//                                (box.front()->children[i])->reverse=(box.front()->reverse)->children[j];
//                                break;
//                            }
//                        }
//                        if(j==26)
//                        {
//                            (box.front()->children[i])->reverse=point;
//                        }


                        tempo=box.front();

                        while(tempo!=point)
                        {
                            if((tempo->reverse)->children[i])
                            {
                                (box.front()->children[i])->reverse=(tempo->reverse)->children[i];
                                (box.front()->children[i])->out|=((tempo->reverse)->children[i])->out;
                                break;
                            }
                            else
                                tempo=tempo->reverse;
                        }

                        if(tempo==point){
                            (box.front()->children[i])->reverse=point;
                            (box.front()->children[i])->out|=point->out;
                        }
                        box.push(box.front()->children[i]);
                       // cout<<(char)('A'+i) <<" ";
                    }
                }
                box.pop();
    }
    //cout<<"done\n";
}
// Returns true if key presents in trie, else 
// false 



int wordCount(struct TrieNode *root) 
{ 
    int result = 0; 
      cout<<"called -----------------\n";
    // Leaf denotes end of a word 
    if (root->isEndOfWord) 
        result++; 
      
    for (int i = 0; i < ALPHABET_SIZE; i++)     
      if (root -> children[i]) 
         result += wordCount(root -> children[i]); 
    
    
    cout<<"result " <<result <<"\n";
    return result;    
} 



long long int search(struct TrieNode *root, string key,int f,int l,int k) 
{      
    map<int,int>::iterator it;
    long long int sum=0;
    int index;
    fav=0;
    ctr=0;
    struct TrieNode *pCrawl = root; 
    struct TrieNode *pCrawlslow = root;
    for (int i = 0; i < key.length(); i++) 
    {     
    
         index = key[i] - 'a'; 
        // cout<<"sezrching for " <<key[i] <<"\n"; 
        if (!pCrawl->children[index])
        {    
            
            if(pCrawl!=root)
            i--;
            pCrawl=pCrawl->reverse;
 
         } 
        else
		{
          
            pCrawlslow=pCrawl;
        pCrawl = pCrawl->children[index];
            if(pCrawl->isEndOfWord)
        {
            //cout<<"ended with out " <<pCrawl->out <<"\n";

            for (int j = 0; j < k; ++j) 
            { 
                if (pCrawl->out & (1 << j)) 
                { 
                    cout << "\nWord " << genes[j] << " appears from "
                        << i - genes[j].length() + 1 << " to " << i << endl; 
                } 
            } 

        }
           // cout<<"yipee found\n";
            struct TrieNode *temp=pCrawl;
            temp=temp->reverse;
            while(temp!=root)
            {
                    if(temp->isEndOfWord)
                    {
                        //cout<<"ended with out " <<temp->out <<"\n";

                        for (int j = 0; j < k; ++j) 
                        { 
                            if (temp->out & (1 << j)) 
                            { 
                                cout << "Word " << genes[j] << " appears from "
                                    << i - genes[j].size() + 1 << " to " << i << endl; 
                            } 
                        } 

                    }
                    temp=temp->reverse;
           
        }
        
         
    } 
    
    }

return sum;
} 

// Driver 
int main() 
{ 

    // Input keys (use only 'a' through 'z' 
    // and lower case) 
    cout<<"Enter the number of keywords\n";
    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout<<"Enter the "<<n <<" keywords seperated by <space> \n";
    string genes_temp_temp;
    getline(cin, genes_temp_temp);

    vector<string> genes_temp = split_string(genes_temp_temp);

    

    for (int i = 0; i < n; i++) {
        string genes_item = genes_temp[i];

        genes.push_back(genes_item);
        
    }

    struct TrieNode *root = getNode(); 
    
    // Construct trie 
    for (int i = 0; i < n; i++) 
        insertt(root, genes[i],i); 

    // Search for different keys 
//    search(root, "an")? cout << "Yes\n" : 
//                        cout << "No\n"; 
//    search(root, "these")? cout << "Yes\n" : 
//                        cout << "No\n"; 



	

    struct TrieNode *pCrawlslow = root;
    settree(pCrawlslow); //building failure links


    cout<<"Enter no of strings to search the keywords?\n";
    int si;
    cin >> si;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int s_itr = 0; s_itr < si; s_itr++) {
    	cout<<"Enter start and end indexes of keywords to be found and the string(eg :0 2 hello)\n";
        string firstLastd_temp;
        getline(cin, firstLastd_temp);

        vector<string> firstLastd = split_string(firstLastd_temp);

        int first = stoi(firstLastd[0]);

        int last = stoi(firstLastd[1]);

        string d = firstLastd[2];
        

    
    long long int c=search(root,d,first,last,genes.size());
    
    cout<<"####################\n";
    sums.push_back(c);
    }
	return 0; 
} 

