% Write a program in prolog/pytholog to implement following simple facts and Queries
% Every child loves Santa.
% Everyone who loves Santa loves any reindeer
% Rudolph is a reindeer, and Rudolph has a red nose
% Anything which has a red nose is weird or is a clown
% No reindeer is a clown
% Scrooge does not love anything which is weird
% (Conclusion) Scrooge is not a child.


% This program is done by CS20B1044 Avinash R Changrani
% Tested it on https://swish.swi-prolog.org/ (this compiler)

% F1 = ∀ x (CHILD(x) → LOVES(x,Santa))
% F2 = ∀ x (LOVES(x,Santa) → ∀ y (REINDEER(y) → LOVES(x,y)))
% F3 = REINDEER(Rudolph) ∧ REDNOSE(Rudolph)
% F4 = ∀ x (REDNOSE(x) → WEIRD(x) ∨ CLOWN(x))
% F5 = ¬ ∃ x (REINDEER(x) ∧ CLOWN(x))
% F6 = ¬ ∃ x (REINDEER(x) ∧ CLOWN(x))
% F7 = ∀ x (WEIRD(x) → ¬ LOVES(Scrooge,x))
% G = ¬ CHILD(Scrooge)

% C1 = ~Child(x) v L(x,Santa)
% C2 = ~L(x,Santa) v ~Reind(y) v L(x,y)
% C3 = Reind(Rudolph)
% C4 = Red(Rudolph)
% C5 = ~Red(x) v Weird(x) v Clown(x)
% C6 = ~Reind(x) v ~ Clown(x)
% C7 = ~Weird(x) v ~L(Scrooge, x)
% C8 =  Child(x)

% By Resolution Refutation

% C9 = C1+ C8 : L(x,Santa)
% C10 = C3+ C6: ~ Clown(Rudolph)
% C11 = C10 + C5 + C4: Weird(Rudolph)
% C12 = C9 + C2: ~Reind(y) v L(x,y)
% C13 = C11 + C7: ~L(Scrooge, Rudolph)
% C14 = C12 + C13: ~Reind(Rudolph)
% C3 + C14 = False

% Negation operator
not(P) :- P, !, fail.
not(_).

% Resolution rule :- (a V b) ^ (~a V c) -> b V c
resolve(Clause1, Clause2, Literal, Result) :-
select(Literal, Clause1, Remaining1),
select(not(Literal), Clause2, Remaining2),
append(Remaining1, Remaining2, Result).

% Function to perform refutation.
refute(Clauses, []) :- member([], Clauses), !.
refute(Clauses, Proof) :-
select(Clause1, Clauses, RemainingClauses),
select(Clause2, RemainingClauses, _),
member(Literal, Clause1),
not(member(not(Literal), Clause2)),
resolve(Clause1, Clause2, Literal, Resolvent),
refute([Resolvent|RemainingClauses], [resolution(Clause1,Clause2,Literal)|Proof]).

% Given Clauses
clauses([
[not, child, X] ; [loves, X, santa],
[not, loves, Y, santa] ; [forAll, Z, ([not, reindeer, Z] ; [loves, Y, Z])],
[reindeer, rudolph],
[rednose, rudolph],
[not, rednose, A] ; [weird, A] ; [clown, A],
[not, [reindeer, B], [clown, B]],
% Negated Conclusion
[child, scrooge] 
]).

% query to run for the compiler to show that the scrooge is not a child.
/** <query>

?- clauses(Clauses), refute(Clauses, Proof).

*/
