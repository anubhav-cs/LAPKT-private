(define (problem Two_Connected_Pits)
(:domain yandi)
(:objects
)
(:init
	(conn node_7_3 node_7_2) (conn node_7_3 node_7_4) (conn node_7_3 node_6_3) (conn node_7_3 node_8_3)	(clear node_7_3) 
	(conn node_1_6 node_1_5) (conn node_1_6 node_1_7) (conn node_1_6 node_2_6)	(clear node_1_6) 
	(conn node_3_7 node_3_6) (conn node_3_7 node_2_7) (conn node_3_7 node_4_7)	(= (tonnage block-node_3_7) 50000) 
	(= (tonnage-extracted block-node_3_7) 0) 
	(= (grade block-node_3_7) 0.60) 
	(at block-node_3_7 node_3_7) 
	(clear node_3_7) 
	(conn node_2_5 node_2_4) (conn node_2_5 node_2_6) (conn node_2_5 node_1_5) (conn node_2_5 node_3_5)	(clear node_2_5) 
	(conn node_8_5 node_8_4) (conn node_8_5 node_8_6) (conn node_8_5 node_7_5) (conn node_8_5 node_9_5)	(clear node_8_5) 
	(conn node_6_7 node_6_6) (conn node_6_7 node_7_7)	(clear node_6_7) 
	(conn node_10_7 node_10_6) (conn node_10_7 node_9_7)	(clear node_10_7) 
	(conn node_7_6 node_7_5) (conn node_7_6 node_7_7) (conn node_7_6 node_6_6) (conn node_7_6 node_8_6)	(clear node_7_6) 
	(conn node_1_1 node_1_2) (conn node_1_1 node_2_1)	(clear node_1_1) 
	(conn node_3_2 node_3_1) (conn node_3_2 node_3_3) (conn node_3_2 node_2_2) (conn node_3_2 node_4_2)	(clear node_3_2) 
	(conn node_2_6 node_2_5) (conn node_2_6 node_2_7) (conn node_2_6 node_1_6) (conn node_2_6 node_3_6)	(clear node_2_6) 
	(conn node_8_2 node_8_1) (conn node_8_2 node_8_3) (conn node_8_2 node_7_2) (conn node_8_2 node_9_2)	(clear node_8_2) 
	(conn node_4_5 node_4_4) (conn node_4_5 node_4_6) (conn node_4_5 node_3_5)	(clear node_4_5) 
	(conn node_9_3 node_9_2) (conn node_9_3 node_9_4) (conn node_9_3 node_8_3) (conn node_9_3 node_10_3)	(clear node_9_3) 
	(conn node_7_5 node_7_4) (conn node_7_5 node_7_6) (conn node_7_5 node_6_5) (conn node_7_5 node_8_5)	(clear node_7_5) 
	(conn node_3_1 node_3_2) (conn node_3_1 node_2_1) (conn node_3_1 node_4_1)	(clear node_3_1) 
	(conn node_2_1 node_2_2) (conn node_2_1 node_1_1) (conn node_2_1 node_3_1)	(clear node_2_1) 
	(conn node_9_4 node_9_3) (conn node_9_4 node_9_5) (conn node_9_4 node_8_4) (conn node_9_4 node_10_4)	(clear node_9_4) 
	(conn node_10_3 node_10_2) (conn node_10_3 node_10_4) (conn node_10_3 node_9_3)	(clear node_10_3) 
	(conn node_7_2 node_7_1) (conn node_7_2 node_7_3) (conn node_7_2 node_6_2) (conn node_7_2 node_8_2)	(clear node_7_2) 
	(conn node_1_5 node_1_4) (conn node_1_5 node_1_6) (conn node_1_5 node_2_5)	(clear node_1_5) 
	(conn node_3_6 node_3_5) (conn node_3_6 node_3_7) (conn node_3_6 node_2_6) (conn node_3_6 node_4_6)	(= (tonnage block-node_3_6) 50000) 
	(= (tonnage-extracted block-node_3_6) 0) 
	(= (grade block-node_3_6) 0.60) 
	(at block-node_3_6 node_3_6) 
	(clear node_3_6) 
	(conn node_2_2 node_2_1) (conn node_2_2 node_2_3) (conn node_2_2 node_1_2) (conn node_2_2 node_3_2)	(clear node_2_2) 
	(conn node_8_6 node_8_5) (conn node_8_6 node_8_7) (conn node_8_6 node_7_6) (conn node_8_6 node_9_6)	(clear node_8_6) 
	(conn node_4_1 node_4_2) (conn node_4_1 node_3_1)	(not (clear node_4_1) ) 
	(at L_4_1 node_4_1) 
	(= (digger-capacity L_4_1) 3000) 
	(= (digger-remaining-time L_4_1) 168) 
	(free L_4_1)
	(conn node_9_7 node_9_6) (conn node_9_7 node_8_7) (conn node_9_7 node_10_7)	(clear node_9_7) 
	(conn node_6_4 node_6_3) (conn node_6_4 node_6_5) (conn node_6_4 node_7_4)	(clear node_6_4) 
	(conn node_10_4 node_10_3) (conn node_10_4 node_10_5) (conn node_10_4 node_9_4)	(clear node_10_4) 
	(conn node_7_1 node_7_2) (conn node_7_1 node_6_1) (conn node_7_1 node_8_1)	(clear node_7_1) 
	(conn node_3_5 node_3_4) (conn node_3_5 node_3_6) (conn node_3_5 node_2_5) (conn node_3_5 node_4_5)	(= (tonnage block-node_3_5) 50000) 
	(= (tonnage-extracted block-node_3_5) 0) 
	(= (grade block-node_3_5) 0.60) 
	(at block-node_3_5 node_3_5) 
	(clear node_3_5) 
	(conn node_2_7 node_2_6) (conn node_2_7 node_1_7) (conn node_2_7 node_3_7)	(clear node_2_7) 
	(conn node_8_3 node_8_2) (conn node_8_3 node_8_4) (conn node_8_3 node_7_3) (conn node_8_3 node_9_3)	(clear node_8_3) 
	(conn node_4_6 node_4_5) (conn node_4_6 node_4_7) (conn node_4_6 node_3_6)	(= (tonnage block-node_4_6) 50000) 
	(= (tonnage-extracted block-node_4_6) 0) 
	(= (grade block-node_4_6) 0.60) 
	(at block-node_4_6 node_4_6) 
	(clear node_4_6) 
	(conn node_9_2 node_9_1) (conn node_9_2 node_9_3) (conn node_9_2 node_8_2) (conn node_9_2 node_10_2)	(clear node_9_2) 
	(conn node_6_1 node_6_2) (conn node_6_1 node_7_1)	(not (clear node_6_1) ) 
	(at L_6_1 node_6_1) 
	(= (digger-capacity L_6_1) 3000) 
	(= (digger-remaining-time L_6_1) 168) 
	(free L_6_1)
	(conn node_7_4 node_7_3) (conn node_7_4 node_7_5) (conn node_7_4 node_6_4) (conn node_7_4 node_8_4)	(clear node_7_4) 
	(conn node_1_3 node_1_2) (conn node_1_3 node_1_4) (conn node_1_3 node_2_3)	(clear node_1_3) 
	(conn node_6_2 node_6_1) (conn node_6_2 node_6_3) (conn node_6_2 node_7_2)	(clear node_6_2) 
	(conn node_1_4 node_1_3) (conn node_1_4 node_1_5) (conn node_1_4 node_2_4)	(clear node_1_4) 
	(conn node_2_3 node_2_2) (conn node_2_3 node_2_4) (conn node_2_3 node_1_3) (conn node_2_3 node_3_3)	(clear node_2_3) 
	(conn node_8_7 node_8_6) (conn node_8_7 node_7_7) (conn node_8_7 node_9_7)	(clear node_8_7) 
	(conn node_4_2 node_4_1) (conn node_4_2 node_4_3) (conn node_4_2 node_3_2)	(clear node_4_2) 
	(conn node_9_6 node_9_5) (conn node_9_6 node_9_7) (conn node_9_6 node_8_6) (conn node_9_6 node_10_6)	(clear node_9_6) 
	(conn node_6_5 node_6_4) (conn node_6_5 node_6_6) (conn node_6_5 node_7_5)	(clear node_6_5) 
	(conn node_5_3 node_4_3) (conn node_5_3 node_6_3)	(clear node_5_3) 
	(conn node_10_5 node_10_4) (conn node_10_5 node_10_6) (conn node_10_5 node_9_5)	(clear node_10_5) 
	(conn node_1_7 node_1_6) (conn node_1_7 node_2_7)	(clear node_1_7) 
	(conn node_3_4 node_3_3) (conn node_3_4 node_3_5) (conn node_3_4 node_2_4) (conn node_3_4 node_4_4)	(= (tonnage block-node_3_4) 50000) 
	(= (tonnage-extracted block-node_3_4) 0) 
	(= (grade block-node_3_4) 0.60) 
	(at block-node_3_4 node_3_4) 
	(clear node_3_4) 
	(conn node_2_4 node_2_3) (conn node_2_4 node_2_5) (conn node_2_4 node_1_4) (conn node_2_4 node_3_4)	(clear node_2_4) 
	(conn node_8_4 node_8_3) (conn node_8_4 node_8_5) (conn node_8_4 node_7_4) (conn node_8_4 node_9_4)	(clear node_8_4) 
	(conn node_4_7 node_4_6) (conn node_4_7 node_3_7)	(= (tonnage block-node_4_7) 50000) 
	(= (tonnage-extracted block-node_4_7) 0) 
	(= (grade block-node_4_7) 0.60) 
	(at block-node_4_7 node_4_7) 
	(clear node_4_7) 
	(conn node_9_1 node_9_2) (conn node_9_1 node_8_1) (conn node_9_1 node_10_1)	(clear node_9_1) 
	(conn node_6_6 node_6_5) (conn node_6_6 node_6_7) (conn node_6_6 node_7_6)	(clear node_6_6) 
	(conn node_10_6 node_10_5) (conn node_10_6 node_10_7) (conn node_10_6 node_9_6)	(clear node_10_6) 
	(conn node_7_7 node_7_6) (conn node_7_7 node_6_7) (conn node_7_7 node_8_7)	(clear node_7_7) 
	(conn node_1_2 node_1_1) (conn node_1_2 node_1_3) (conn node_1_2 node_2_2)	(clear node_1_2) 
	(conn node_3_3 node_3_2) (conn node_3_3 node_3_4) (conn node_3_3 node_2_3) (conn node_3_3 node_4_3)	(clear node_3_3) 
	(conn node_8_1 node_8_2) (conn node_8_1 node_7_1) (conn node_8_1 node_9_1)	(clear node_8_1) 
	(conn node_4_4 node_4_3) (conn node_4_4 node_4_5) (conn node_4_4 node_3_4)	(clear node_4_4) 
	(conn node_6_3 node_6_2) (conn node_6_3 node_6_4) (conn node_6_3 node_5_3) (conn node_6_3 node_7_3)	(clear node_6_3) 
	(conn node_10_1 node_10_2) (conn node_10_1 node_9_1)	(clear node_10_1) 
	(conn node_4_3 node_4_2) (conn node_4_3 node_4_4) (conn node_4_3 node_3_3) (conn node_4_3 node_5_3)	(clear node_4_3) 
	(conn node_9_5 node_9_4) (conn node_9_5 node_9_6) (conn node_9_5 node_8_5) (conn node_9_5 node_10_5)	(clear node_9_5) 
	(conn node_10_2 node_10_1) (conn node_10_2 node_10_3) (conn node_10_2 node_9_2)	(clear node_10_2) 
	(= (total-cost) 0) 
	(= (grade-tonnage build) 0) 
	(= (tonnage-extracted build) 0) 
	(not-reset-tonnage) 
	(not-update-tonnage) 
	(= (tonnage build) 280000) 
)
(:goal
(and
 	(= (tonnage block-node_3_7) 0) 
	(= (tonnage block-node_3_6) 0) 
	(= (tonnage block-node_3_5) 0) 
	(= (tonnage block-node_4_6) 0) 
	(= (tonnage block-node_3_4) 0) 
	(= (tonnage block-node_4_7) 0) 
		(digged-block-node_4_7-build-0) 
		(digged-block-node_4_6-build-0) 
		(digged-block-node_3_6-build-0) 
		(digged-block-node_3_7-build-0) 
		(partially-digged-block-node_3_4-build-0) 
		(digged-block-node_3_5-build-0) 

)
)
(:metric minimize (total-cost))
)
