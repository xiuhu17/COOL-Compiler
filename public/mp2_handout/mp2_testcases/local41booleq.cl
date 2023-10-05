-- Primary test for '=' operator.
-- Applies '=' for Int and Bool, and for false and true cases.
-- Result should be 1.

class Main {
    main(): Int {
	(if (not 3 = 5) then
	   if (not true = false) then
	     if (false = false) then
	       1
	     else
	       2 fi
	    else 3 fi
	 else 4 fi)
    };
};
