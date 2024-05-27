SOLVED: Bug1: when doing 6. Dashboard the Revenues on that specific selected month are not printed. 
    idea: make it print expenses then \n and then print revenues the same as expenses were printed 

Bug2: Goals Tab when doing 2. See Goal/s the printing gets real bad.
    idea: manage the way the printing is cleared and the space required for printing, inspire from other table printing 
            - must have the ending message asking the user for cin.ignore() in order to return back to GoalsTab

Bug3: Doing from the mainMenu 5. Investments Tab the screen is not cleared and
            the printing is bad must be in the center of the screen

Bug4: When investing again in a already present stock instead of updating the quantity for that stock,
    another stock is created....

<<<Implemented not really tested, but pretty much working as expected>>>
Missing Functionality: create velocity in the price of the stock, have stock prices 
        and the user can have a number of stocks (float) of a quantity of money 
        1. each stock should be bought in shares.
        2. each stock has a share price that modifies.
        3. devident calculation per month for each stock and the price difference for each month
        4. when you want to see dashboard the program will ask the user in which month he is in 
        5. depending on the month the price is different, you can see the difference in the stock value
        6. maybe implement something like more percentages where random choice is garanteed of the stock price
        7. stock price as an idea; 0.5% increase decrease ... 1% maybe one bad one 10% down and good one 14% up
        8. optional further idea if everything works make the devidents different % per month depending on stock wise

menu idea:
    
    1. Invest in a Stock 
        ->
            Select the Stock 
                (the user is given 10 stocks) with prices printed/share
            How many Share do you want to buy ?
                > user input ex: 10
            Your receipt is : buy 10 * $156.80 = $1568.00 are you sure you want to proceed with this action ?
                > user input Y/N
            return to menu
    2. View Investment Portfolio
        should print: username | stockname | owned shares | price  | total   | difference of price (+/-)| devidents_this_month (based on percentage %4.2)
                        mlem   |  GOOGL    |     10       | 159.21 | 1592.10 |          10.23(+)        |       52.50$
    3. Sell Shares:
        -> 
            Select The Stock
                (the user is given his stocks) with prices printed/ share ammount
            How many Shares do you want to sell ?
                > user input ex: 10
            Your receipt is : sell 10 * $182.80 = 1828.00 are you sure you want ot proceed with this action ?  
                > user input Y/N
            here the initial price that the user have bought the shares is used to find the profit the user got after selling the stock
                print the profit/loss the user made selling this stock  (based only on the price of the stock bought time/ sold time , not devidents) 
            return to menu

the structure of the file should be very well organized for easy retrieval
