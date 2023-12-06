-- Example of static and dynamic type differing, and some other stuff

Class Book inherits IO {
    title : String;
    author : String;

    initBook(title_p : String, author_p : String) : Book {
        {
            title <- title_p;
            author <- author_p;
            self;
        }
    };

	getSelf() : Object {
		self
	};

    print(s : String) : String {
        {
            s <- s.concat("title:      ").concat(title).concat("\n");
            s.concat("author:     ").concat(author).concat("\n");
        }
    };
};

Class Article inherits Book {
    per_title : String;

    initArticle(title_p : String, author_p : String,
		per_title_p : String) : Article {
        {
            initBook(title_p, author_p);
            per_title <- per_title_p;
            self;
        }
    };

	getSelf() : Object {
		self
	};

    print(s : String) : String {
        {
	    s <- self@Book.print(s);
        s.concat("periodical:  ").concat(per_title).concat("\n");
        }
    };
};

Class BookList inherits IO { 
    (* Since abort "returns" type Object, we have to add
       an expression of type Bool here to satisfy the typechecker.
       This code is unreachable, since abort() halts the program.
    *)
    isNil() : Bool { { abort(); true; } };
    
    cons(hd : Book) : Cons {
        (let new_cell : Cons <- new Cons in
            new_cell.init(hd,self)
        )
    };

    (* Since abort "returns" type Object, we have to add
       an expression of type Book here to satisfy the typechecker.
       This code is unreachable, since abort() halts the program.
    *)
    car() : Book { { abort(); new Book; } };
    
    (* Since abort "returns" type Object, we have to add
       an expression of type BookList here to satisfy the typechecker.
       This code is unreachable, since abort() halts the program.
    *)
    cdr() : BookList { { abort(); new BookList; } };
    
    print_list(s : String) : String { "" };
};

Class Cons inherits BookList {
    xcar : Book;  (* We keep the car and cdr in attributes. *)
    xcdr : BookList; (* Because methods and features must have different names, *)
    (* we use xcar and xcdr for the attributes and reserve *)
    (* car and cdr for the features. *)
    
    isNil() : Bool { false };
    
    init(hd : Book, tl : BookList) : Cons {
        {
            xcar <- hd;
            xcdr <- tl;
            self;
        }
    };

    car() : Book { xcar };

    cdr() : BookList { xcdr };
    
    print_list(s : String) : String {
        {
            s <- xcar.print(s);
			s <-
			case xcar.getSelf() of
				dummy : Book => s.concat("- dynamic type was Book -\n");
				dummy : Article => s.concat("- dynamic type was Article -\n");
			esac;
            xcdr.print_list(s);
        }
    };
};

Class Nil inherits BookList {
    isNil() : Bool { true };

    print_list(s : String) : String { s };
};


Class Main {

    books : BookList;

    main() : String {
        (let a_book : Book <-
            (new Book).initBook("Compilers, Principles, Techniques, and Tools",
                                "Aho, Sethi, and Ullman")
        in
            (let an_article : Article <-
                (new Article).initArticle("The Top 100 CD_ROMs",
                                          "Ulanoff",
                                          "PC Magazine")
            in
                {
                    books <- (new Nil).cons(a_book).cons(an_article);
                    books.print_list("");
                }
            )  (* end let an_article *)
        )  (* end let a_book *)
    };
};
