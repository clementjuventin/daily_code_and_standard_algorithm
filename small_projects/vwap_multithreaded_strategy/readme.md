Using this dataset https://www.kaggle.com/datasets/imranbukhari/comprehensive-ethusd-1m-data?resource=download.

I will try to provide the VWAP (Volume-Weighted Average Price) indicator.

The idea is that I have a CSV file containing the ETH/USD price data every minute for a set of cryptocurrencies exchanges. I will code an engine pushing data to a queue and a set of workers consuming this data to calculate the VWAP.