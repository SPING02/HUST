-- 11) 给出黄姓用户的编号、名称、办理的银行卡的数量(没有办卡的卡数量计为0),持卡数量命名为number_of_cards,
--     按办理银行卡数量降序输出,持卡数量相同的,依客户编号排序。
-- 请用一条SQL语句实现该查询：
-- output list
SELECT c_id, c_name, ifnull(number_of_cards, 0) AS number_of_cards
FROM client 
-- left join bank_card table to get count of data shows on same c_id
LEFT JOIN (SELECT b_c_id, COUNT(*) AS number_of_cards FROM bank_card
GROUP BY b_c_id
ORDER BY number_of_cards DESC) 
-- number_of_cards_table created 
number_of_cards_table ON client.c_id=number_of_cards_table.b_c_id
-- to screening surname of client is黄
WHERE c_name like '黄%'
ORDER BY number_of_cards DESC, c_id

/*  end  of  your code  */ 