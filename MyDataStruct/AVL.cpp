//
// Created by Han on 16/3/25.
//
#include <iostream>

using namespace std;

//平衡因子的值
const int LH = 1;
const int EH = 0;
const int RH = -1;

//结构
class Avl
{
public:
    int val;//值
    int bf;//平衡因子
    Avl* left;
    Avl* right;
    Avl(): val(-1),bf(EH),left(NULL),right(NULL) {}
    Avl(int value){
        val = value;
        bf = EH;
        left = NULL;
        right = NULL;
    }
};

//右旋转
void R_rotate(Avl* &tree)
{
    Avl* lc = tree->left;
    Avl* p = lc->right;
    lc->right = tree;
    tree->right = p;
    tree = lc;
}

//左旋转
void L_rotate(Avl* &tree)
{
    Avl* rc = tree->right;
    Avl* p = rc->left;
    rc->left = tree;
    tree->right = p;
    tree = rc;
}

//左平衡: 包括LL 和 LR
void LeftBalance(Avl* &tree)
{
    Avl* lc = tree->left;
    switch (lc->bf){
        //LL:
        case LH:
            tree->bf = EH;
            lc->bf = EH;
            R_rotate(tree);
            break;
         //LR:
        case RH:
            Avl* lc_rc = lc->right;
            switch (lc_rc->bf){
                case LH:
                    lc->bf = EH;
                    tree->bf = RH;
                    break;
                case EH:
                    lc->bf = EH;
                    tree->bf = EH;
                    break;
                case RH:
                    lc->bf = LH;
                    tree->bf = EH;
                    break;
            }
            lc_rc->bf = EH;
            L_rotate(tree->left);
            R_rotate(tree);
            break;
    }
}

//右平衡:包括 RR 和 RL
void RightBalance(Avl* &tree)
{
    Avl* rc = tree->right;
    switch(rc->bf){
        //RR:
        case RH:
            tree->bf = EH;
            rc->bf = EH;
            L_rotate(tree);
            break;
            //RL:
        case LH:
            Avl* rc_lc = rc->right;
            switch (rc_lc->bf){
                case LH:
                    rc->bf = RH;
                    tree->bf = EH;
                    break;
                case EH:
                    rc->bf = EH;
                    tree->bf = EH;
                    break;
                case RH:
                    rc->bf = EH;
                    tree->bf = LH;
            }
            rc_lc->bf = EH;
            R_rotate(tree->right);
            L_rotate(tree);
            break;
    }
}

void DelAvl(Avl* &tree, int value, bool &shorter)
{
    if(tree == NULL){//未找到
        return;
    }
    if(tree->val == value){//找到
        if(tree->left == NULL){
            //左子树为空
            Avl* q = tree;
            tree = tree->right;
            delete q;
            shorter = true;
        }else if(tree->right == NULL){
            //右子树为空
            Avl* q = tree;
            tree = tree->left;
            delete q;
            shorter = true;
        }else{
            //左右子树均非空:
            Avl* q = tree->left;
            while(q->right != NULL){
                q = q->right;//前驱结点
            }
            tree->val = q->val;
            DelAvl(tree->left,q->val,shorter);//删除前驱结点
            if(shorter){
                //左子树变矮
                switch (tree->bf){
                    case RH:
                        RightBalance(tree);
                        shorter = false;
                        break;
                    case EH:
                        tree->bf=RH;
                        shorter = false;
                        break;
                    case LH:
                        tree->bf = EH;
                        shorter = true;
                        break;
                }
            }
        }
    }
    else if(value > tree->val){//右子树
        DelAvl(tree->right, value, shorter);
        if(shorter){
            //右子树变矮:
            switch(tree->bf){
                case RH:
                    tree->bf = EH;
                    shorter = true;
                    break;
                case EH:
                    tree->bf = LH;
                    shorter = false;
                    break;
                case LH:
                    LeftBalance(tree);
                    shorter = false;
                    break;
            }
        }
    }else{//左子树
        DelAvl(tree->left,value,shorter);
        if(shorter){
            //左子树变矮
            switch (tree->bf){
                case RH:
                    RightBalance(tree);
                    shorter = false;
                    break;
                case EH:
                    tree->bf=RH;
                    shorter = false;
                    break;
                case LH:
                    tree->bf = EH;
                    shorter = true;
                    break;
            }
        }
    }
}


void InsertAvl(Avl* &tree, int value,bool &taller)
{
    if(tree == NULL){
        tree = new Avl(value);
        taller = true;
    }
    if(value < tree->val){//插入左子树
        InsertAvl(tree->left,value,taller);
        if(taller){//子树变高
            switch(tree->bf){
                case LH:
                    LeftBalance(tree);
                    taller = false;
                    break;
                case EH:
                    taller = true;
                    tree->bf = LH;
                    break;
                case RH:
                    taller = false;
                    tree->bf = EH;
                    break;
            }
        }
    } else if(value > tree->val){//插入右子树
        InsertAvl(tree->right,value,taller);
        if(taller){//子树变高
            switch(tree->bf){
                case LH:
                    taller = false;
                    tree->bf = EH;
                    break;
                case EH:
                    taller = true;
                    tree->bf = RH;
                    break;
                case RH:
                    RightBalance(tree);
                    taller = false;
                    break;
            }
        }
    }
}

int main()
{

}