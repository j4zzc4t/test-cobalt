
#include "comparator.hxx"
#include <ranges>
#define ALLOWED_HIST_DIVERGENCE 1 // the number of characters difference between mask and target, 0 means strong comparison
#define ALLOWED_EXCESS          4 // the number of allowed excessive characters

void Comparator::create_hist(std::string &word, histogram &target_hist){

    for (int i = 0; i < word.size(); i++){
        convert_character(word[i], target_hist);
    }

}

std::vector<histogram> Comparator::prepare_data(std::vector<std::string> &vec){
    // to conserve space and cpu we use lists 
    // if we find a similar histogram we'll just track back to the original string to verify 
    // trackback is possible as we keep the order and indices of the original word list    
    std::vector<histogram> result;
    for ( std::string w : vec)
    {
        histogram new_hist;
        create_hist(w, new_hist);
        result.push_back(new_hist); 
    }

    return result;
}


std::vector<std::string> Comparator::find_similar(std::string &word, std::vector<std::string> &targets){
    
    //the key api function, calls and processes all the stuff from high level
    histogram mask;
    create_hist(word, mask);
 
    std::vector<histogram> to_search = prepare_data(targets);
    std::vector<uint> similar; 
    
    for(int i = 0; i < to_search.size(); i++ ){
        if(compare_hists(mask, to_search[i]))
        {
            similar.push_back(i);
        }
    }

    //after we narrow down the hists which are similar in composition to our mask target
    //we can compare the order and verify those are not anagrams
    return verify(word, similar, targets);
}


std::vector<std::string> Comparator::verify(std::string &mask, std::vector<uint> &indices, std::vector<std::string> &targets){
    // here we verify the word is indeed structurally similar by 
    // checking the order of consonants
    // so even if initial comparison of Alexander and Oleksandr fails
    // it will detect that to a certain degree those names are similar
    // due to there not being any disorders in the word order 
    std::vector<std::string> result;
    for (auto i : indices)
    {
       std::string target = targets[i];

       uint last_pos = 0;
       uint inconsistency_counter = 0;
       bool popped = false;

       for (auto ch : mask)
       {   
           auto pos = target.find(ch);
        
           if(pos == std::string::npos){
               inconsistency_counter++;
           }


           if(pos < last_pos || inconsistency_counter > ALLOWED_EXCESS || inconsistency_counter == ALLOWED_EXCESS)
           {
               indices.pop_back();
               popped = true;
               break;  
           }

           if(pos != std::string::npos){
               target[pos] = ' '; //cleaning searched to get rid of duplicates
           }
           last_pos = pos;
       }
       if (popped) 
       {
           popped = false; //reset the flag
           continue;
       }
       result.push_back(targets[i]);  
       
    }

    return result;
}

bool Comparator::compare_hists(histogram &mask, histogram &target){
    //we use the desired word histogram as a mask and look if the other histogram has similarities
    
    uint excesses_counter = 0;
    uint misses_counter = 0;
    for (uint i=0; i < 26; i++){
        if(mask.counters[i] == 0 && target.counters[i] != 0){
            excesses_counter++;
            if( excesses_counter > ALLOWED_EXCESS)
            {
                return false; // excess non-mask letters are less important, but we still have to track their divergence 
            }
            continue; 
        }
        else if (mask.counters[i] == 0){
            continue; //we skip checking for the empty ones in the mask
        }
        else{

            char select  = mask.counters[i]   - target.counters[i]; // not enough similar characters
            char exclude = target.counters[i] - mask.counters[i]; // too much simiilar characters
            if( abs(select) > ALLOWED_HIST_DIVERGENCE || abs(exclude) > ALLOWED_HIST_DIVERGENCE )
            {
                misses_counter++;
                if(misses_counter > ALLOWED_HIST_DIVERGENCE)
                {
                    return false; //too much divergence, not enough characters in the target to resemble the mask 
                }
            }
            else {
                continue;
            }
        }
    }
    //if we go over all of the word and there is no heavy divergence from the mask
    //we declare histograms are similar enough
    return true;
}



void Comparator::convert_character(char &character, histogram &target_hist){
    //i'm sorry but this has to be a very long switch
    //we count each letter in the desired word and create a histogram of a word contents
    switch(character){
        case 'a': target_hist.counters[0]++; break;
        case 'b': target_hist.counters[1]++; break;
        case 'c': target_hist.counters[2]++; break;
        case 'd': target_hist.counters[3]++; break;
        case 'e': target_hist.counters[4]++; break;
        case 'f': target_hist.counters[5]++; break;
        case 'g': target_hist.counters[6]++; break;
        case 'h': target_hist.counters[7]++; break;
        case 'i': target_hist.counters[8]++; break;
        case 'j': target_hist.counters[9]++; break;
        case 'k': target_hist.counters[10]++; break;
        case 'l': target_hist.counters[11]++; break;
        case 'm': target_hist.counters[12]++; break;
        case 'n': target_hist.counters[13]++; break;
        case 'o': target_hist.counters[14]++; break;
        case 'p': target_hist.counters[15]++; break;
        case 'q': target_hist.counters[16]++; break;
        case 'r': target_hist.counters[17]++; break;
        case 's': target_hist.counters[18]++; break;
        case 't': target_hist.counters[19]++; break;
        case 'u': target_hist.counters[20]++; break;
        case 'v': target_hist.counters[21]++; break;
        case 'w': target_hist.counters[22]++; break;
        case 'x': target_hist.counters[23]++; break;
        case 'y': target_hist.counters[24]++; break;
        case 'z': target_hist.counters[24]++; break;
        case 'A': target_hist.counters[0]++; break;
        case 'B': target_hist.counters[1]++; break;
        case 'C': target_hist.counters[2]++; break;
        case 'D': target_hist.counters[3]++; break;
        case 'E': target_hist.counters[4]++; break;
        case 'F': target_hist.counters[5]++; break;
        case 'G': target_hist.counters[6]++; break;
        case 'H': target_hist.counters[7]++; break;
        case 'I': target_hist.counters[8]++; break;
        case 'J': target_hist.counters[9]++; break;
        case 'K': target_hist.counters[10]++; break;
        case 'L': target_hist.counters[11]++; break;
        case 'M': target_hist.counters[12]++; break;
        case 'N': target_hist.counters[13]++; break;
        case 'O': target_hist.counters[14]++; break;
        case 'P': target_hist.counters[15]++; break;
        case 'Q': target_hist.counters[16]++; break;
        case 'R': target_hist.counters[17]++; break;
        case 'S': target_hist.counters[18]++; break;
        case 'T': target_hist.counters[19]++; break;
        case 'U': target_hist.counters[20]++; break;
        case 'V': target_hist.counters[21]++; break;
        case 'W': target_hist.counters[22]++; break;
        case 'X': target_hist.counters[23]++; break;
        case 'Y': target_hist.counters[24]++; break;
        case 'Z': target_hist.counters[24]++; break;
    }
}
