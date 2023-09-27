#pragma once

/*

�R���e�i�n�^�C�v�錾�p�w�b�_�[
�����I�ɂ�Using����f�t�H���g��STL����؂�ւ���B

*/

#include <vector>
#include <array>
#include <map>
#include <unordered_map>
#include <list>
#include <forward_list>
#include <deque>
#include <queue>
#include <stack>

template<typename T>
using TVariableArray = std::vector<T>;

template<typename T>
using TFixedArray = std::array<T>;

template<typename T>
using TMap = std::map<T>;

template<typename T>
using TUnorderedMap = std::unordered_map<T>;

template<typename T>
using TList = std::list<T>;

template<typename T>
using TForwardList = std::forward_list<T>;

template<typename T>
using TDeque = std::deque<T>;

template<typename T>
using TQueue = std::queue<T>;

template<typename T>
using TStack = std::stack<T>;