#include <iostream>
using namespace std;

struct NoArvore{
	int key;
	int fb;
	NoArvore *esquerda;
	NoArvore *direita;
};

void exibirArvore(NoArvore *raiz){
	if(raiz != NULL){
		exibirArvore(raiz -> esquerda);
		cout <<"Chave: " <<raiz -> key << ", FB: " << raiz->fb << " / ";
		exibirArvore(raiz -> direita);
	}
}

int heightArvore(NoArvore *raiz){
	if(raiz == NULL){
		return 0;
	}else{
		if(raiz -> esquerda == NULL && raiz -> direita == NULL){
			return 1;
		}else if(raiz -> esquerda != NULL && raiz -> direita != NULL){
			if(heightArvore(raiz -> direita) >= heightArvore(raiz -> esquerda)){
				return 1 + heightArvore(raiz -> direita);
			}else{
				return 1 + heightArvore(raiz -> esquerda);
			}
		}else if(raiz -> esquerda != NULL){
			return 1 + heightArvore(raiz -> esquerda);
		}else{
			return 1 + heightArvore(raiz -> direita);
		}
	}
}

NoArvore *rotacaoDireita(NoArvore *&raiz){
	if(raiz != NULL && raiz -> esquerda != NULL){
		NoArvore *aux = raiz;
		raiz = raiz -> esquerda;
		aux -> esquerda = NULL;
		if(raiz -> direita != NULL){
			aux -> esquerda = raiz -> direita;
		}
		raiz -> direita = aux;
	}
	return raiz;
}

NoArvore *rotacaoEsquerda(NoArvore *&raiz){
	if(raiz != NULL && raiz -> direita != NULL){
		NoArvore *aux = raiz;
		raiz = raiz -> direita;
		aux -> direita = NULL;
		if(raiz -> esquerda != NULL){
			aux -> direita = raiz -> esquerda;
		}
		raiz -> esquerda = aux;	
	}
	return raiz;
}

NoArvore *rotacaoDuplaDireita(NoArvore *&raiz){
	if(raiz != NULL && raiz -> esquerda != NULL){
		rotacaoEsquerda(raiz -> esquerda);
		return rotacaoDireita(raiz);
	}
}

NoArvore *rotacaoDuplaEsquerda(NoArvore *&raiz){
	if(raiz != NULL && raiz -> direita != NULL){
		rotacaoDireita(raiz -> direita);
		return rotacaoEsquerda(raiz);
	}
}

void atualizarFb(NoArvore *&raiz){
	if(raiz != NULL){
		raiz -> fb = heightArvore(raiz -> esquerda) - heightArvore(raiz -> direita);
		atualizarFb(raiz -> esquerda);
		atualizarFb(raiz -> direita);
	}
}

NoArvore *balancearAVL(NoArvore *&raiz){
	if(raiz != NULL){
		balancearAVL(raiz -> esquerda);
		balancearAVL(raiz -> direita);
		atualizarFb(raiz);
		if(raiz -> fb > 1){
			if(raiz -> esquerda -> fb >= 0){
				return rotacaoDireita(raiz);
			}else{
				return rotacaoDuplaDireita(raiz);
			}
		}else if(raiz -> fb < -1){
			if(raiz -> direita -> fb <= 0){
				return rotacaoEsquerda(raiz);
			}else{
				return rotacaoDuplaEsquerda(raiz);
			}
		}
		return raiz;
	}
}

NoArvore *inserirBST(NoArvore *&raiz, int chave){
	if(raiz == NULL){
		NoArvore *novoNo = new NoArvore;
		novoNo -> key = chave;
		novoNo -> fb = 0;
		novoNo -> esquerda = NULL;
		novoNo -> direita = NULL;
		raiz = novoNo;
		return raiz;
	} else if(chave < raiz -> key){
		return inserirBST(raiz->esquerda, chave);
	} else if(chave > raiz -> key){
		return inserirBST(raiz->direita, chave);
	}else{
		cout << "Chave ja existe." << endl;
	}
}

 NoArvore *inserirAVL(NoArvore *&raiz, int chave){
	inserirBST(raiz, chave);
	raiz = balancearAVL(raiz);
	atualizarFb(raiz);
	return raiz;
}

/*
NoArvore *busca(NoArvore *raiz, int chave){
	if(raiz == NULL){
		cout << "Aluno nao encontrado" << endl;
		return raiz;
	}else if(raiz -> key == chave){
		cout << "Nome: " << raiz -> aluno.nome << endl;
		cout << "CPF: " << raiz -> aluno.cpf << endl;
		cout << "Idade: " << raiz -> aluno.idade << endl;
		return raiz;
	} else if(chave < raiz -> key){
		busca(raiz -> esquerda, chave);
	} else {
		busca(raiz -> direita, chave);
	}
}*/

void *deletarBST(NoArvore *&raiz, int chave){
	if(chave > raiz -> key){
		deletarBST(raiz -> direita, chave);
	}else if(chave < raiz -> key){
		deletarBST(raiz -> esquerda, chave);
	} else {
		NoArvore *aux = raiz;
		if(raiz -> esquerda == NULL && raiz -> direita == NULL){
			raiz = NULL;
			delete raiz;
		}else if(raiz -> esquerda == NULL){
			NoArvore *aux = raiz;
			raiz = raiz -> direita;
			delete aux;
		}else if(raiz -> direita == NULL){
			NoArvore *aux = raiz;
			raiz = raiz -> esquerda;
			delete aux;
		}else{
			NoArvore *aux = raiz;
			NoArvore *maiorEsquerda = raiz -> esquerda;
			while(maiorEsquerda -> direita != NULL){
				maiorEsquerda = maiorEsquerda -> direita;
			}
			deletarBST(raiz, maiorEsquerda->key);
			raiz = maiorEsquerda;
			if(aux -> esquerda != raiz){
				raiz -> esquerda = aux -> esquerda;
			}
			raiz -> direita = aux -> direita;
			aux = NULL;
			delete aux;
		}
	}
}

void *deletarAVL(NoArvore *&raiz, int chave){
	deletarBST(raiz, chave);
	raiz = balancearAVL(raiz);
	atualizarFb(raiz);
}

int main() {
	NoArvore *no1 = NULL;
	inserirAVL(no1, 15);
	cout << "Inseri a raiz: ";
	exibirArvore(no1);
	cout << endl;
	inserirAVL(no1, 22);
	cout << "Inseri alguns nos: ";
	exibirArvore(no1);
	cout << endl;
	inserirAVL(no1, 27);
	cout << "Inseri alguns nos: ";
	exibirArvore(no1);
	cout << endl;
	inserirAVL(no1, 2);
	inserirAVL(no1, 10);
	cout << "Inseri alguns nos: ";
	exibirArvore(no1);
	cout << endl;
	/*
	cout << "Busca aluno da chave 2: " << endl;
	busca(no1, 2);
	*/
	cout << "Deletei o no da chave 10: " << endl;
	deletarAVL(no1, 10);
	exibirArvore(no1);
	cout << endl;
	return 0;
}
