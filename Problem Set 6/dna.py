def main():
    # Define variables to use
    table = []
    match = {}
    user = 'No match'

    # Make user submit a proper argument
    if len(sys.argv) != 3:
        print("Usage: dna.py [database.csv] [sequence.txt]")
        sys.exit()

    # Open database file and make a table list
    with open(sys.argv[1], 'r') as db_file:
        db = csv.DictReader(db_file)
        for row in db:
            table.append(row)
    db_file.close()

    # Open sequence file and make a sequence string
    seq_file = open(sys.argv[2], 'r')
    sequence = seq_file.read()
    seq_file.close()

    # Grab table names, since the value is integer
    # I can specifically grab those names to pass
    # for longest_match
    tbl_name = [key for key, value in table[0].items() if value.isdigit()]

    # Store the matches
    for name in tbl_name:
        m = longest_match(sequence, name)
        match[name] = m

    # Check in table list if someone matched the whole criteria
    for row in table:
        user_matched = True

        for key in match:
            if int(row.get(key)) != int(match[key]):
                user_matched = False
                break

        if user_matched:
            user = row['name']
            break

    # Finally, print the user
    return print(user)
