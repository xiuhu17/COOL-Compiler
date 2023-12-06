-- Primary test for if-then-else
-- computes (n/2)/2 for constant n = 14
-- result should be (n/2)/2 = 3

class Main {
    main(): Int {
	(let n: Int in {
	    n <- 14;				-- n = 14
	    let m: Int in {
	        if (n < 8) then {		-- n > 8 so:
		    m <- n*2;
		} else {
		    m <- n/2;			-- m = 7
	        } fi;
	        m / 2;				-- result should be 3
	    };
         })
    };
};
