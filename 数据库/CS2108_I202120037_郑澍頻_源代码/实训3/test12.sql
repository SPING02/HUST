-- 12) 综合客户表(client)、资产表(property)、理财产品表(finances_product)、保险表(insurance)和
 --     基金表(fund)，列出客户的名称、身份证号以及投资总金额（即投资本金，
 --     每笔投资金额=商品数量*该产品每份金额)，注意投资金额按类型需要查询不同的表，
 --     投资总金额是客户购买的各类资产(理财,保险,基金)投资金额的总和，总金额命名为total_amount。
 --     查询结果按总金额降序排序。
 -- 请用一条SQL语句实现该查询：

-- output listafter sum is total_amount = amount per property type * property quantity
SELECT c_name, c_id_card, SUM(ifnull(p_amount, IFNULL(i_amount, IFNULL(f_amount, 0)))*IFNULL(pro_quantity,0)) AS total_amount
FROM
-- SELECT output list FROM union_table
-- which union_table include table client, property, finance_property, insurans, fund
-- SELECT c_id to left join property
-- SELECT c_name and c_id_card to OUTPUT
-- SELECT every table's amount and property quantity from each table and left join amount table with client table using pro_pif_id and pro type
(SELECT client.c_id, client.c_name, client.c_id_card, finances_product.p_amount, insurance.i_amount, fund.f_amount, property.pro_quantity
FROM client
LEFT JOIN property ON client.c_id=property.pro_c_id
LEFT JOIN finances_product ON property.pro_pif_id=finances_product.p_id AND pro_type=1
LEFT JOIN insurance ON property.pro_pif_id=insurance.i_id AND pro_type=2
LEFT JOIN fund ON property.pro_pif_id=fund.f_id AND pro_type=3)AS union_table
GROUP BY c_id
ORDER BY total_amount DESC


/*  end  of  your code  */ 