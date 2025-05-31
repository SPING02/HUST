-- 3) 查询购买了所有畅销理财产品的客户
--   请用一条SQL语句实现该查询：

-- output list
\
SELECT pro_c_id
FROM (
   -- to get pro_c_id for output list and cnt1 cnt2 
   -- cnt1 is COUNT(pro_c_id) of table3
   -- cnt2 is COUNT(*) of table1 = number of best-selling financial products
   -- table1 and table2 is to get best-selling financial products
   SELECT pro_c_id, COUNT(pro_c_id)AS cnt1, cnt2 FROM(
      SELECT pro_c_id, pro_pif_id,(
         SELECT COUNT(*) FROM(
            SELECT pro_pif_id
            FROM property
            WHERE pro_type=1
            GROUP BY pro_pif_id
            HAVING COUNT(DISTINCT(pro_c_id))>=3
         )AS table1
      )AS cnt2
      FROM property
      NATURAL JOIN 
      (
         SELECT pro_pif_id
         FROM property
         WHERE pro_type=1
         GROUP BY pro_pif_id
         HAVING COUNT(DISTINCT(pro_c_id))>=3
      )AS table2
      WHERE pro_type=1
      ORDER BY pro_c_id
   )AS table3
   GROUP BY pro_c_id\
)AS table4
WHERE cnt1=cnt2;

/*  end  of  your code  */