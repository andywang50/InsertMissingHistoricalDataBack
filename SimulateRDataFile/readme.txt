Readme -- Simulate RData.

IMPORTANT: Required Package: RInside. need to link manually. Follow https://www.youtube.com/watch?v=sjiSaaNA8BY to link RInside package.
		If you are using XCode and no txt files or Rdata files are created, follow this link: https://www.quora.com/Why-is-Xcode-not-writing-me-a-txt-file

This program randomly generates the trading data of some futures over several days.
	E.g. Futures: CLF8, CLM8, CLX8.
		 Dates: 2017-12-06, 2017-12-07, 2012-12-08.

The prices are simulated using Monte Carlo simulation of Black-Scholes model.

Only records the rows where trade happens.

Outputs: 2017.12.06.CLF8.RData, 2017.12.06.CLF8.txt, etc.

Columns explanation:
	time: in milliseconds; GMT time
	Bid.Price, Ask.Price, Trade.Price: randomly generated using B-S.
	Bid.Size, Ask.Size, Volume: random integer from 0 to 3.