from main_test import main


def simulate():
    params = {'remove': False, 'alpha': 1.01, 'number_encoding' : 2,'number_increments': 100,'number_expriments': 20,'number_of_repeats':500}
    main(params)
    params = {'remove': False, 'alpha': 1.1, 'number_encoding' : 2,'number_increments': 100,'number_expriments': 20,'number_of_repeats':100}
    main(params)
    params = {'remove': False, 'alpha': 1.1, 'number_encoding' : 2,'number_increments': 100,'number_expriments': 20,'number_of_repeats':500}
    main(params)
    params = {'remove': False, 'alpha': 1.5, 'number_encoding' : 2,'number_increments': 100,'number_expriments': 20,'number_of_repeats':500}
    main(params)

simulate()