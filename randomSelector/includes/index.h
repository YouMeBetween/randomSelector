#ifndef _INDEX_H_
#define _INDEX_H_

constexpr int MAIN_MENU_INDEX = 1;
constexpr int RESULT_SHOW_INDEX = 2;
constexpr int SETTING_INDEX = 3;
constexpr int ITEMS_SETUP_INDEX = 4;
constexpr int PAGE_JUMP_INDEX = 5;
constexpr int ADD_ITEMS_INDEX = 6;
constexpr int EDIT_ITEMS_INDEX = 7;
constexpr int ITEMS_LIST_SETTING_INDEX = 8;
constexpr int ADD_LIST_INDEX = 9;
constexpr int NO_LINE = -1;
constexpr int RESULT_SHOW_LINE_IN_MAIN_MENU = 3;
constexpr int SETTING_LINE_IN_MAIN_MENU = 4;
constexpr int WEIGHT_SELECT_IN_SETTING = 3;
constexpr int ITEM_LIST_SETTING_IN_SETTING = 5;
constexpr int ITEM_SETUP_IN_SETTING = 6;
constexpr int ITEMS_PER_PAGE_IN_ITEMS_SETUP = 5;
constexpr int LIST_PER_PAGE_IN_ITEMS_LIST_SETTING = 5;
/* ��λ��ʾpageJump���������
 * �����λ��ʼÿλ��ʾ���������£�
 * 0b001λ��0������������������1��������������ת
 * 0b010λ��0�����治������itemsSetup���棻1������������itemsSetup����
 * 0b100λ��0�����治������itemsListSetting���棻1������������itemsListSetting����
 */
constexpr int ITEMS_SETUP_SEARCH_INDEX = 0b010;
constexpr int ITEMS_SETUP_JUMP_INDEX = 0b011;
constexpr int ITEMS_LIST_SETTING_SEARCH_INDEX = 0b100;
constexpr int ITEMS_LIST_SETTING_JUMP_INDEX = 0b101;

#endif // !_INDEX_H_
