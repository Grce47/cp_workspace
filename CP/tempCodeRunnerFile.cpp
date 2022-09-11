//swap
                        for(int x=0;x<3;x++)
                        {
                            for(int y=x+1;y<3;y++)
                            {
                                int mn = min(cnt[x][perm[y]],cnt[y][perm[x]]);
                                cnt[x][perm[y]] -= mn;
                                cnt[y][perm[x]] -= mn;
                                cnt[x][perm[x]] += mn;
                                cnt[y][perm[y]] += mn;
                                ans += mn;
                            }
                        }