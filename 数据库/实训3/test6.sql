-- 6) 查询资产表中所有资产记录里商品收益的众数和它出现的次数。
--    请用一条SQL语句实现该查询：
/*众数：一组数据中出现最多次的数*/
/*出现的次数 as presence*/
SELECT pro_income, COUNT(*) AS presence
FROM property GROUP BY pro_income
HAVING COUNT(pro_income) >= all(select COUNT(pro_income) FROM property GROUP BY pro_income);
/*  end  of  your code  */