#include <iostream>
#pragma once
//Реализовать на основе обычного дерева поиска.Сбалансированность поддерживать не требуется.
//Контейнер должен предоставлять как минимум следующие методы:
//1. Печать дерева : void print() const
//2. Вставка нового элемента :
//Вариант 1 : bool insert(int key)
//Вариант 2 : bool insert(int key, string value)
//3. Поиск элемента :
//Вариант 1 : bool find(int key) const
//Вариант 2 : const string & find(int key) const
//4. Удаление элемента : bool erase(int key)
struct node {
	long long key;
	node* left;
	node* right;
	unsigned height;
	node(int k){
	key = k; left = right = 0; height = 1;}
};
class Set {
	node* root;
	unsigned height(node* root) {
		return root ? root->height : 0;
	};
	void fix_height(node* root){
		unsigned h_l = height(root->left);
		unsigned h_r = height(root->right);
		root->height = (h_l > h_r ? h_l : h_r) + 1;
	};
	int balance_factor(node* root) {
		return height(root->right) - height(root->left);
	};
	node* rotate_left(node* root) {
		node* p = root->right;
		root->right = p->left;
		p->left = root;
		fix_height(root);
		fix_height(p);
		return p;

	};
	node* rotate_right(node* root) {
		node* q = root->left;
		root->left = q->right;
		q->right = root;
		fix_height(root);
		fix_height(q);
		return q;
	};
	node* balance(node* root) {
		fix_height(root);
		if (balance_factor(root) == 2)
		{
			if (balance_factor(root->right) < 0)
				root->right = rotate_right(root->right);
			return rotate_left(root);
		}
		if (balance_factor(root) == -2)
		{
			if (balance_factor(root->left) > 0)
				root->left = rotate_left(root->left);
			return rotate_right(root);
		}
		return root; // балансировка не нужна
	};
	node* insert(node* root, int key){
	
		if (!root) return new node(key);
		if (key < root->key) root->left = insert(root->left, key);
		else if (key == root->key) return root;//throw("The element already exist");
		else root->right = insert(root->right, key);
		return balance(root);
	};
	node* erase_elem(node* root, int key) {
		if (!root) return nullptr;
		if (key < root->key)
		{
			root->left = erase_elem(root->left, key);
		}
		else if (key > root->key)
		{
			root->right = erase_elem(root->right, key);
		}
		else
		{
			node* temp_l = root->left;
			node* temp_r = root->right;
			delete root;
			if (!temp_r) return temp_l;
			if (!temp_l) return temp_r;
			node* min = find_min(temp_r);
			min->right = erase_min(temp_r);
			min->left = temp_l;
			return balance(min);
		}
		return balance(root);
	};
	void delete_tree(node* root) {
		if (root){
			delete_tree(root->right);
			delete_tree(root->left);
			delete root;
		}
	};
	void print(node* root, int step) const {
		if (root){
			print(root->right, step + 1);
			for (int i = 0; i < step; i++)
				std::cout << "   ";
			std::cout << root->key << std::endl;
			print(root->left, step + 1);
		}
	};
	node* find_min(node* root) {
		return root->left ? find_min(root->left) : root;
	};
	node* erase_min(node* root) {
		if (root->left == nullptr) return root->right;
		root->left = erase_min(root->left);
		return balance(root);
	};
public:
	Set() {root = nullptr;
	};
	Set(int k) {
		root = insert(root, k);
	}
	~Set() {
		delete_tree(root);
		root = nullptr;
	};
	void print() const {
		if (root) print(root, 0);
		else std::cout << "Tree is empty";
	};
	bool insert(int key) {
		root = insert(root, key);
		return true;
	};
	bool find(int key) const {
		if (!root)
		{
			std::cout << "Tree is empty";
			return false;
		}
		node* temp = root;
		while (temp != nullptr)
		{
			if (key < temp->key) temp = temp->left;
			else if (key > temp->key) temp = temp->right;
			else if (key == temp->key) return true;
		}
		return false;
	};
	bool erase(int key) {
		root = erase_elem(root, key);
		return true;
	};
};