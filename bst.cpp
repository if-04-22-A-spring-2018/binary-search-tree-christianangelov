#include "bst.h"
#include <stdlib.h>
#include <stdio.h>
#include "general.h"

struct Node{
  int data;
  Bst left_subtree;
  Bst right_subtree;
};

Bst new_bst(){
  Bst root = 0;
  return root;
}
void delete_bst(Bst bst){
  if(bst == 0){
    return;
  }

  delete_bst(bst->left_subtree);
  delete_bst(bst->right_subtree);
  sfree(bst);

}

int get_depth(Bst bst){
  if(bst == 0){
    return 0;
  }
  int depth_left = get_depth(bst->left_subtree) + 1;
  int depth_right = get_depth(bst->right_subtree) + 1;
  if (depth_left > depth_right) {
    return depth_left;
  }
  else{
    return depth_right;
  }
}
void add(Bst* bst, int value){

  Bst &newBst = *bst;
  if (newBst == 0) {
    newBst = (Bst)malloc(sizeof(struct Node));
    newBst->data = value;
    newBst->left_subtree = 0;
    newBst->right_subtree = 0;
  }
  else if(value <= newBst->data) {
      add(&newBst->left_subtree, value);
  }
  else {
    add(&newBst->right_subtree, value);
  }

}
int root_value(Bst bst){
  if (bst != 0) {
    return bst->data;
  }
  return 0;
}
Bst left_subtree(Bst root){
  if (root->left_subtree != 0) {
    return root->left_subtree;
  }
  return 0;
}
Bst right_subtree(Bst root){
  if (root->right_subtree != 0) {
    return root->right_subtree;
  }
  return 0;
}
int traverse_pre_order(Bst bst, int *elements, int start){
  if(bst == 0){
    return 0;
  }
  int number_of_steps = 0;
  elements[start] = bst->data;
  number_of_steps += 1;
  number_of_steps += traverse_pre_order(bst->left_subtree, elements, start + 1);
  number_of_steps += traverse_pre_order(bst->right_subtree, elements, start + number_of_steps);

  return number_of_steps;
}

int traverse_in_order(Bst bst, int *elements, int start){
  if(bst == 0){
    return 0;
  }
  int number_of_steps = 0;
  number_of_steps += traverse_in_order(bst->left_subtree, elements, start);
  elements[start + number_of_steps] = bst->data;
  number_of_steps += 1;
  number_of_steps += traverse_in_order(bst->right_subtree, elements, start + number_of_steps);
  
  return number_of_steps;
}

int traverse_post_order(Bst bst, int *elements, int start){
  if(bst == 0){
    return 0;
  }
  int number_of_steps = 0;
  number_of_steps += traverse_post_order(bst->left_subtree, elements, start);
  number_of_steps += traverse_post_order(bst->right_subtree, elements, start + number_of_steps);
  elements[start + number_of_steps] = bst->data;

  return number_of_steps + 1;
}
bool are_equal(Bst bst1, Bst bst2){

  if(bst1 == bst2){
    return true;

  }
  if(bst1 != 0 && bst2 != 0){

    int first_array[25];
    int length_first = traverse_in_order(bst1, first_array, 0);

    int second_array[25];
    int length_second = traverse_in_order(bst2, second_array, 0);

    if(length_first == length_second){
      bool is_equal = true;
    for (int i = 0; i < length_first; i++) {
      if(first_array[i] != second_array[i])
      is_equal = false;
    }
    return is_equal;
  }
  return false;
  }
}

void most_left_longest_branch(Bst bst, Bst* branch){
  if(bst == 0){
    return;
  }


   add(branch, bst->data);
   if(get_depth(bst->left_subtree) >= get_depth(bst->right_subtree)){
     most_left_longest_branch(bst->left_subtree, branch);
   }
   else{
     most_left_longest_branch(bst->right_subtree, branch);
   }
}


int get_number_of_subtrees(Bst bst){
  if(bst == 0){
    return -1;
  }
  return get_number_of_subtrees(bst->left_subtree) + 1 + get_number_of_subtrees(bst->right_subtree) + 1;
}
