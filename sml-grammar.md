# Core Language

## Constants
con	    ::=	int	                integer
            word	            word
            float	            floating point
            char	            character
            string	            string
int	    ::=	⟨~⟩num	            decimal
            ⟨~⟩0xhex	        hexadecimal
word	::=	0wnum	            decimal
            0wxhex	            hexadecimal
float	::=	⟨~⟩num.num	        floating point
            ⟨~⟩num⟨.num⟩e⟨~⟩num scientific
char	::=	#"ascii"	        character
string  	::=	"⟨ascii⟩\*"	    string
num	    ::=	⟨digit⟩+	        number
hex	    ::=	⟨digit | letter⟩+   hexadecimal number (letters may only be in the range A-F)
ascii	::=	...	                single non-" ASCII character or \-headed escape sequence

## Identifiers
id	    ::=	letter⟨letter | digit | ' | _⟩\*	                                                alphanumeric
            ⟨! | % | & | $ | # | + | - | / | : | < | = | > | ? | @ | \ | ~ | ` | ^ | | | \*⟩+  	symbolic (not allowed for type variables or module language identifiers)
var	    ::=	'⟨letter | digit | ' | _⟩\*	                                                        unconstrained
            ''⟨letter | digit | ' | _⟩\*                                                        equality
longid  ::= id1.···.idn	                                                                        qualified (n ≥ 1)
lab	    ::=	id	                                                                                identifier
            num	                                                                                number (may not start with 0)

## Expressions
exp	    ::= con	                                constant
            ⟨op⟩ longid	                        value or constructor identifier
            exp1 exp2	                        application
            exp1 id exp2	                    infix application
            ( exp )	                            parentheses
            ( exp1 , ... , expn )	            tuple (n ≠ 1)
            { ⟨exprow⟩ }   	                    record
            \# lab	                            record selector
            [ exp1 , ... , expn ]	            list (n ≥ 0)
            ( exp1 ; ... ; expn )	            sequence (n ≥ 2)
            let dec in exp1 ; ... ; expn end    local declaration (n ≥ 1)
            exp : typ	                        type annotation
            raise exp	                        exception raising
            exp handle match	                exception handling
            exp1 andalso exp2	                conjunction
            exp1 orelse exp2	                disjunction
            if exp1 then exp2 else exp3	        conditional
            while exp1 do exp2	                iteration
            case exp of match	                case analysis
            fn match	                        function
exprow  ::=	lab = exp ⟨, exprow⟩	            expression row
match   ::=	pat => exp ⟨| match⟩	            match

## Patterns
pat   	::= con	                            constant
            _	                            wildcard
            ⟨op⟩ id	                        variable
            ⟨op⟩ longid ⟨pat⟩	            construction
            pat1 id pat2	                infix construction
            ( pat )	                        parentheses
            ( pat1 , ... , patn )	        tuple (n ≠ 1)
            { ⟨patrow⟩ }   	                record
            [ pat1 , ... , patn ]	        list (n ≥ 0)
            pat : typ	                    type annotation
            ⟨op⟩ id ⟨: typ⟩ as pat	        layered
patrow  ::=	...	                            wildcard
            lab = pat ⟨, patrow⟩	        pattern
            id ⟨: typ⟩ ⟨as pat⟩ ⟨, patrow⟩  variable

## Types
typ   	::= var	variable
            ⟨typ⟩(,) longid	        constructor
            ( typ )	                parentheses
            typ1 -> typ2	        function
            typ1 * ... * typn	    tuple (n ≥ 2)
            { ⟨typrow⟩ }   	        record
typrow  ::=	lab : typ ⟨, typrow⟩    type row

## Declarations
dec	    ::=	val ⟨var⟩(,) valbind	                                    value
            fun ⟨var⟩(,) funbind	                                    function
            type typbind	                                            type
            datatype datbind ⟨withtype typbind⟩	                        data type
            datatype id = datatype longid	                            data type replication
            abstype datbind ⟨withtype typbind⟩ with dec end	            abstract type
            exception exnbind	                                        exception
            structure strbind	                                        structure (not allowed inside expressions)
                                                                        empty
            dec1 ⟨;⟩ dec2	                                            sequence
            local dec1 in dec2 end	                                    local
            open longid1 ... longidn	                                inclusion (n ≥ 1)
            nonfix id1 ... idn	                                        nonfix (n ≥ 1)
            infix ⟨digit⟩ id1 ... idn	                                left-associative infix (n ≥ 1)
            infixr ⟨digit⟩ id1 ... idn	                                right-associative infix (n ≥ 1)
valbind	::=	pat = exp ⟨and valbind⟩	                                    destructuring
            rec valbind	                                                recursive
funbind	::=	funmatch ⟨and funbind⟩	                                    clausal function
funmatch::=	⟨op⟩ id pat1 ... patn ⟨: typ⟩ = exp ⟨| funmatch⟩   	        nonfix (n ≥ 1)
            pat1 id pat2 ⟨: typ⟩ = exp ⟨| funmatch⟩	                    infix
            ( pat1 id pat2 ) pat'1 ... pat'n ⟨: typ⟩ = exp ⟨| funmatch⟩ infix (n ≥ 0)
typbind	::=	⟨var⟩(,) id = typ ⟨and typbind⟩	                            abbreviation
datbind	::=	⟨var⟩(,) id = conbind ⟨and datbind⟩   	                    data type
conbind	::=	id ⟨of typ⟩ ⟨| conbind⟩   	                                data constructor
exnbind ::=	id ⟨of typ⟩ ⟨and exnbind⟩	                                generative
            id = longid ⟨and exnbind⟩	                                renaming
Note: Omitted op on constructors.

# Module Language

## Structures
str   	::= longid	identifier
            struct dec end	structure
            str : sig	transparent annotation
            str :> sig	opaque annotation
            id ( str )	functor application
            id ( dec )	functor application
            let dec in str end   	local declaration
strbind ::=	id ⟨:⟨>⟩ sig⟩ = str ⟨and strbind⟩   	structure

## Signatures
sig	    ::= id  identifier
            sig spec end	signature
            sig where type typrefin	refinement
            typrefin	::=	⟨var⟩(,) longid = typ ⟨and type typrefin⟩	type refinement
spec	::=	val valdesc	value
            type typdesc	type
            eqtype typdesc	equality type
            type typbind	type abbreviation
            datatype datdesc	data type
            datatype id = datatype longid	data type replication
            exception exndesc	exception
            structure strdesc	structure
            empty
            spec1 ⟨;⟩ spec2	sequence
            include sigexp	inclusion
            include id1 ... idn	inclusion (n ≥ 1)
            spec sharing type longid1 = ... = longidn   	type sharing (n ≥ 2)
            spec sharing longid1 = ... = longidn	structure sharing (n ≥ 2)
valdesc	::=	id : typ ⟨and valdesc⟩	value
typdesc	::=	⟨var⟩(,) id ⟨and typdesc⟩	abstract type
datdesc	::=	⟨var⟩(,) id = condesc ⟨and datdesc⟩   	data type
condesc	::=	id ⟨of typ⟩ ⟨| condesc⟩   	data constructor
exndesc ::=	id ⟨of typ⟩ ⟨and exndesc⟩	exception
strdesc	::=	id : sig ⟨and strdesc⟩	structure

## Programs
prog	::= dec	core declaration
            functor fctbind	functor declaration
            signature sigbind	signature declaration
            empty
            prog1 ⟨;⟩ prog2	sequence
fctbind	::=	id1 ( id2 : sig ) ⟨:⟨>⟩ sig⟩ = str ⟨and fctbind⟩   	plain
            id ( spec ) ⟨:⟨>⟩ sig⟩ = str ⟨and fctbind⟩	opened
sigbind   	::=	id = sig ⟨and sigbind⟩	signaturee
