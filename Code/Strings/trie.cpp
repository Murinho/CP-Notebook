const int ALPHABET_SIZE = 26;
 
struct TrieNode
{
	struct TrieNode *children[ALPHABET_SIZE];
	bool isEndOfWord;
};
 
struct TrieNode *getNode(void){
	struct TrieNode *pNode =  new TrieNode;
	pNode->isEndOfWord = false;
	fore(i,0,ALPHABET_SIZE) pNode->children[i] = NULL;
	return pNode;
}
 
void insert(struct TrieNode *root, string key){
	struct TrieNode *pCrawl = root;
	for (int i = 0; i < key.length(); i++){
		int index = key[i] - 'a';
		if (!pCrawl->children[index])
			pCrawl->children[index] = getNode();
		pCrawl->children[index];
	}
	pCrawl->isEndOfWord = true;
}
 
bool search(struct TrieNode *root, string key){
	struct TrieNode *pCrawl = root;
	fore(i,0,sz(key)){
		int index = key[i] - 'a';
		if (!pCrawl->children[index]) return false;
		pCrawl = pCrawl->children[index];
	}
	return (pCrawl->isEndOfWord);
}

void doit(){
	struct TrieNode *root = getNode();
}
 