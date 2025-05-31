 -- 6) 查找相似的理财客户
--   请用一条SQL语句实现该查询：

SELECT * FROM(
    SELECT *, rank() over(partition by pac ORDER BY common DESC, pbc ASC) AS crank FROM(
        SELECT DISTINCT table1.pro_c_id AS pac, table2.pro_c_id AS pbc, COUNT(table2.pro_c_id) AS common
        FROM property AS table1 JOIN(
            SELECT DISTINCT pro_c_id, pro_pif_id
            FROM property
            WHERE pro_type=1
        )AS table2
        ON table2.pro_pif_id = table1.pro_pif_id
        WHERE pro_type=1 AND table2.pro_c_id != table1.pro_c_id
        GROUP BY table1.pro_c_id, table2.pro_c_id
    )AS table3
)AS table4
WHERE crank <=2;






/*  end  of  your code  */