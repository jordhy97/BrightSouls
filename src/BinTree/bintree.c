#include <stdio.h>
#include <stdlib.h>
#include "bintree.h"

#define max(a,b) ((a) > (b) ? (a) : (b))

BinTree Tree (infotype Akar, BinTree L, BinTree R) {
    BinTree P;
    P = AlokNode(Akar);
    if (P != Nil) {
        Left(P) = L;
        Right(P) = R;
    }
    return P;
}

void MakeTree (infotype Akar, BinTree L, BinTree R, BinTree *P) {
    *P = Tree(Akar,L,R);
}

addrNode AlokNode (infotype X) {
    addrNode P;
    P = (Node*)malloc(sizeof(Node));
    if (P != Nil) {
        Akar(P) = X;
        Left(P) = Nil;
        Right(P) = Nil;
    }
    return P;
}

void DealokNode (addrNode P) {
    free(P);
}

boolean IsTreeEmpty (BinTree P) {
    return P == Nil;
}

boolean IsTreeOneElmt (BinTree P) {
    return !IsTreeEmpty(P) && Left(P) == Nil && Right(P) == Nil;
}

boolean IsUnerLeft (BinTree P) {
    return !IsTreeEmpty(P) && Left(P) != Nil && Right(P) == Nil;
}

boolean IsUnerRight (BinTree P) {
    return !IsTreeEmpty(P) && Left(P) == Nil && Right(P) != Nil;
}

boolean IsBiner (BinTree P) {
    return !IsTreeEmpty(P) && Left(P) != Nil && Right(P) != Nil;
}

void PrintPreorder (BinTree P) {
    if (IsTreeEmpty(P)) {
        printf("()");
    }
    else {
        printf("(");
        printf("%d",Akar(P));
        PrintPreorder(Left(P));
        PrintPreorder(Right(P));
        printf(")");
    }
}

void PrintInorder (BinTree P) {
    if (IsTreeEmpty(P)) {
        printf("()");
    }
    else {
        printf("(");
        PrintInorder(Left(P));
        printf("%d",Akar(P));
        PrintInorder(Right(P));
        printf(")");
    }
}

void PrintPostorder (BinTree P) {
    if (IsTreeEmpty(P)) {
        printf("()");
    }
    else {
        printf("(");
        PrintPostorder(Left(P));
        PrintPostorder(Right(P));
        printf("%d",Akar(P));
        printf(")");
    }
}

void PrintTree1 (BinTree P, int h, int bil) {
    if (IsTreeOneElmt(P)) {
        printf("%d\n",Akar(P));
    }
    else {
        int i;
        printf("%d\n",Akar(P));
        if (Left(P) != Nil) {
            for (i = 1; i <= bil; ++i) {
                printf(" ");
            }
            PrintTree1(Left(P),h,bil+h);
        }
        if (Right(P) != Nil) {
            for (i = 1; i <= bil; ++i) {
                printf(" ");
            }
            PrintTree1(Right(P),h,bil+h);
        }
    }
}

void PrintTree (BinTree P, int h) {
    PrintTree1(P,h,h);
}

boolean SearchTree (BinTree P, infotype X) {
    if (IsTreeEmpty(P)) {
        return false;
    }
    else {
        if (Akar(P) == X) {
            return true;
        }
        else {
            return SearchTree(Left(P),X) || SearchTree(Right(P),X);
        }
    }
}

int NbElmt (BinTree P) {
    if (IsTreeEmpty(P)) {
        return 0;
    }
    else {
        return 1 + NbElmt(Left(P)) + NbElmt(Right(P));
    }
}

int NbDaun (BinTree P) {
    if (IsTreeOneElmt(P)) {
        return 1;
    }
    else {
        if (IsUnerLeft(P)) {
            return NbDaun(Left(P));
        }
        else if (IsUnerRight(P)) {
            return NbDaun(Right(P));
        }
        else {
            return NbDaun(Left(P)) + NbDaun(Right(P));
        }
    }
}

boolean IsSkewLeft (BinTree P) {
    if (IsTreeEmpty(P)) {
        return true;
    }
    else {
        if (IsUnerRight(P) || IsBiner(P)) {
            return false;
        }
        else {
            return IsSkewLeft(Left(P));
        }
    }
}

boolean IsSkewRight (BinTree P) {
    if (IsTreeEmpty(P)) {
        return true;
    }
    else {
        if (IsUnerLeft(P) || IsBiner(P)) {
            return false;
        }
        else {
            return IsSkewRight(Right(P));
        }
    }
}

int TreeLevel (BinTree P, infotype X) {
    if (Akar(P) == X) {
        return 1;
    }
    else {
        if (SearchTree(Left(P),X)) {
            return 1 + TreeLevel(Left(P),X);
        }
        else {
            return 1 + TreeLevel(Right(P),X);
        }
    }
}

int Tinggi (BinTree P) {
    if (IsTreeEmpty(P)) {
        return 0;
    }
    else {
        return 1 + max(Tinggi(Left(P)),Tinggi(Right(P)));
    }
}

void AddDaunTerkiri (BinTree *P, infotype X) {
    if (IsTreeEmpty(*P)) {
        *P = AlokNode(X);
    }
    else {
        AddDaunTerkiri(&Left(*P),X);
    }
}

void AddDaun (BinTree *P, infotype X, infotype Y, boolean Kiri) {
    if (IsTreeOneElmt(*P)) {
        addrNode Pt;
        Pt = AlokNode(Y);
        if (Kiri) {
            Left(*P) = Pt;
        }
        else {
            Right(*P) = Pt;
        }
    }
    else {
        if (SearchTree(Left(*P),X)) {
            AddDaun(&Left(*P),X,Y,Kiri);
        }
        else {
            AddDaun(&Right(*P),X,Y,Kiri);
        }
    }
}

void DelDaunTerkiri (BinTree *P, infotype *X) {
    if (IsTreeOneElmt(*P)) {
        addrNode N;
        *X = Akar(*P);
        N = *P;
        *P = Nil;
        DealokNode(N);
    }
    else {
        if (IsUnerRight(*P)) {
            DelDaunTerkiri(&Right(*P),X);
        }
        else {
            DelDaunTerkiri(&Left(*P),X);
        }
    }
}

void DelDaun (BinTree *P, infotype X) {
    if (IsTreeOneElmt(*P)) {
        addrNode N;
        N = *P;
        *P = Nil;
        DealokNode(N);
    }
    else {
        if (SearchTree(Left(*P),X)) {
            DelDaun(&Left(*P),X);
        }
        if (SearchTree(Right(*P),X)) {
            DelDaun(&Right(*P),X);
        }
    }
}

