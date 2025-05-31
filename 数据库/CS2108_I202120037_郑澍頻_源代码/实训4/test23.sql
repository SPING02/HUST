-- 4) 	查找相似的理财产品

--   请用一条SQL语句实现该查询：
SELECT pro_pif_id, cc , dense_rank() over(ORDER BY cc DESC) AS prank
FROM(
    -- to get number of client for each property
    SELECT pro_pif_id, COUNT(pro_c_id) AS cc FROM(
        -- to get Products held by the 3 customers with the largest number of products
        SELECT pro_pif_id FROM(
            -- to get 3 customers with the largest number of products
            SELECT pro_c_id FROM(
                -- rank of client
                SELECT pro_c_id, cnt, dense_rank()over(ORDER BY cnt DESC) AS rk FROM(
                    -- number of products held by each client
                    SELECT pro_c_id, COUNT(pro_pif_id) AS cnt
                    FROM property
                    WHERE pro_pif_id=14 and pro_type=1
                    GROUP BY pro_c_id
                )AS table1
            )AS table2
            -- top3
            WHERE rk<=3
        )AS table3
        NATURAL JOIN property WHERE property.pro_type=1 AND property.pro_pif_id<>14
    )AS table4
    NATURAL JOIN property WHERE property.pro_type=1
    GROUP BY pro_pif_id
    ORDER BY pro_pif_id
)AS table5;







/*  end  of  your code  */